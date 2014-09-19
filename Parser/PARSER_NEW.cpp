#include "PARSER_NEW.h"
#include "../Scanner/Scanner.h"
#include <iostream>
#include <time.h> // For measuring the compilation time

using std::cout;
using std::endl;
using std::cerr;

ParserNEW::ParserNEW(Scanner *scanner, OutBuffer *out) {
  clock_t start, end;
  int typeErrors, parseErrors;
  start = clock();

//  ListTChain<StatementNEW>* ltc = new ListTChain<StatementNEW>();
//  delete ltc;

  scanner->nextToken();
  cout << "Starting parsing..." << endl;

  prog = new ProgNEW(scanner, out, parseErrors, typeErrors);
  prog->typeCheck();
  prog->makeCode(out);

  end = clock();
  if(!typeErrors && !parseErrors)
    cout << "Parsing complete" << endl << "Used time: "  << (double)(end-start)/CLOCKS_PER_SEC << " s" << endl;
  else
    cout << "Parsing failed" << endl << "Used time: "  << (double)(end-start)/CLOCKS_PER_SEC << " s" << endl;
}

ParserNEW::~ParserNEW() {
  if(prog)
    delete prog;
}

Node::Node(Scanner* scanner) {
  this->scanner = scanner;
  cloneTokenData();
}

Node::~Node() {}

int Node::mark = 1;
unsigned int Node::parseErrors = 0;
unsigned int Node::typeErrors = 0;

void Node::cloneTokenData() {
  line = scanner->token->getLine();
  column = scanner->token->getColumn();
  value = scanner->token->getValue();
  info = scanner->token->getInformation();
}

void Node::parseError(const char* message) {
  cout << "Parse error at [" << line << ":" << column << "] (" << info->getLexem() <<  ") :"  << message  << endl;
  nodeType = ERROR_TYPE;
  parseErrors++;
}

void Node::typeError(const char* message) {
  cout << "Type error at [" << line << ":" << column << "] (" << info->getLexem() <<  ") :"  << message  << endl;
  nodeType = ERROR_TYPE;
  typeErrors++;
}

ProgNEW::ProgNEW(Scanner* scanner, OutBuffer* out, int& pE, int &tE) : Node(scanner) {
  decls = new DeclsNEW(scanner, out, pE, tE);
//  delete decls; // do this in ParserNEW's constructure after typeCheck() and makeCode() have been executed!
  statements = new StatementsNEW(scanner, out, pE, tE);
//  delete statements; // do this in ParserNEW's constructure after typeCheck() and makeCode() have been executed!
  pE = parseErrors;
  tE = typeErrors;
}

ProgNEW::~ProgNEW() {
  if(decls)
    delete decls;
  if(statements)
    delete statements;
}

void ProgNEW::typeCheck() {
  decls->typeCheck();
  statements->typeCheck();
}

void ProgNEW::makeCode(OutBuffer *out) {
  decls->makeCode(out);
  statements->makeCode(out);
  (*out) << "STP\n";
}

DeclsNEW::DeclsNEW(Scanner* scanner, OutBuffer* out, int& pE, int &tE) : Node(scanner) {
  decls = new ListT<DeclNEW>();

  while(scanner->token->getInformation()->equals("int")) {
    scanner->newIdentifier();
    decls->append(new DeclNEW(scanner, out, pE, tE));
    if(scanner->token->getInformation()->getType() == TTYPE_SEMI) {
      scanner->nextToken();
      cloneTokenData();
    }
    else
      parseError("Missing ';'");
  }
}

DeclsNEW::~DeclsNEW() {
  if(decls)
    delete decls;
}

void DeclsNEW::typeCheck() {
  ListTElement<DeclNEW>* tmp = decls->getFirst();

  while (tmp) {
    tmp->getData()->typeCheck(); // check type of each decl in the list of decls
    tmp = tmp->getNext();
  }
}

void DeclsNEW::makeCode(OutBuffer *out) {
  ListTElement<DeclNEW>* tmp = decls->getFirst();

  while (tmp) {
    tmp->getData()->makeCode(out); // make code for each decl in the list of decls
    tmp = tmp->getNext();
  }
}

DeclNEW::DeclNEW(Scanner* scanner, OutBuffer* out, int& pE, int &tE) : Node(scanner) {
  array = new ArrayNEW(scanner, out, pE, tE);

  if (scanner->token->getInformation()->getType() == TTYPE_CONFIRMED_IDENTIFIER) {
    info = scanner->token->getInformation();
    scanner->nextToken();
//    cloneTokenData();
  } else
    parseError("New identifier expected");
}

DeclNEW::~DeclNEW() {
  if(array)
    delete array;
}

void DeclNEW::typeCheck() {
  array->typeCheck();

  if (scanner->token->getInformation()->getType() == TTYPE_EXISTING_IDENTIFIER) {
    typeError("identifer already defined");
    nodeType = ERROR_TYPE;
  }
  else if (array->nodeType == ERROR_TYPE)
    nodeType = ERROR_TYPE;
  else {
    nodeType = NO_TYPE;

    if (array->nodeType == ARRAY_TYPE)
      info->toArray();
  }
}

void DeclNEW::makeCode(OutBuffer *out) {
  (*out) << "DS $" << info->getLexem();
  array->makeCode(out);
}

ArrayNEW::ArrayNEW(Scanner* scanner, OutBuffer* out, int& pE, int &tE) : Node(scanner) {
  if (scanner->token->getInformation()->getType() == TTYPE_S_B_O) {
    value = -1;
    scanner->nextToken();

    if (scanner->token->getInformation()->getType() == TTYPE_INT) {
      value = scanner->token->getValue();
      scanner->nextToken();

      if (scanner->token->getInformation()->getType() == TTYPE_S_B_C) {
        scanner->newIdentifier();
        nodeType = ARRAY_TYPE;
      }
      else
        parseError("Missing closing ']'");
    }
    else
      parseError("Integer value expected");
  }
  else
    nodeType = NO_TYPE; // in case of a non-array variable
}

ArrayNEW::~ArrayNEW() {}

void ArrayNEW::typeCheck() {
  if(nodeType == ARRAY_TYPE && value < 1) {
    typeError("No valid dimension");
    nodeType = ERROR_TYPE;
  }
}

void ArrayNEW::makeCode(OutBuffer *out) {
  if (nodeType == ARRAY_TYPE)
    (*out) << " " << value << "\n";
  else
    (*out) << " " << 1 << "\n";
}

IndexNEW::IndexNEW(Scanner* scanner, OutBuffer* out, int& pE, int &tE) : Node(scanner), exp(0) {
  if (scanner->token->getInformation()->getType() == TTYPE_S_B_O) {
    scanner->nextToken();
    exp = new ExpNEW(scanner, out, pE, tE);

    if (scanner->token->getInformation()->getType() == TTYPE_S_B_C)
      scanner->nextToken();
    else
      parseError("Missing closing ']'");
  }
}

IndexNEW::~IndexNEW() {
  if(exp)
    delete exp;
}

void IndexNEW::typeCheck() {
  if (exp) {
    exp->typeCheck();

    if (exp->nodeType == ERROR_TYPE)
      nodeType = ERROR_TYPE;
    else
      nodeType = ARRAY_TYPE;
  }
  else
    nodeType = NO_TYPE;
}

void IndexNEW::makeCode(OutBuffer *out) {
  if (exp) {
    exp->makeCode(out);
    (*out) << "ADD\n";
  }
}

StatementsNEW::StatementsNEW(Scanner* scanner, OutBuffer* out, int& pE, int &tE) : Node(scanner) {
  statements = new ListT<StatementNEW>();

  while (scanner->token->getInformation()->getType() != TTYPE_FILE_END && nodeType != ERROR_TYPE && scanner->token->getInformation()->getType() != TTYPE_C_B_C) {
    statements->append(new StatementNEW(scanner, out, pE, tE));

    if (scanner->token->getInformation()->getType() == TTYPE_SEMI) {
      scanner->nextToken();
      cloneTokenData();
    }
    else
      parseError("Missing ';'");
  }
}

StatementsNEW::~StatementsNEW() {
  // delete each element in the ListT
  if(statements)
    delete statements;
}

void StatementsNEW::typeCheck() {
  ListTElement<StatementNEW>* tmp = statements->getFirst();

  while (tmp) {
    tmp->getData()->typeCheck(); // make code for each decl in the list of decls
    tmp->getData()->nodeType = NO_TYPE;
    tmp = tmp->getNext();
  }
}

void StatementsNEW::makeCode(OutBuffer *out) {
  ListTElement<StatementNEW>* tmp = statements->getFirst();

  while (tmp) {
    tmp->getData()->makeCode(out); // make code for each decl in the list of decls
    tmp = tmp->getNext();
  }
}

StatementNEW::StatementNEW(Scanner* scanner, OutBuffer* out, int& pE, int &tE) : Node(scanner), jumpBackMark(0), jumpForwardMark(0), statement1(0), statement2(0), statements(0) {
  if (scanner->token->getInformation()->getType() == TTYPE_CONFIRMED_IDENTIFIER || scanner->token->getInformation()->getType() == TTYPE_ARRAY) {
    scanner->nextToken();
    index = new IndexNEW(scanner, out, pE, tE);

    if (scanner->token->getInformation()->getType() == TTYPE_EQUALS) {
      scanner->nextToken();
      exp = new ExpNEW(scanner, out, pE, tE);
      statementType = STATEMENT_ASSIGN;
    }
    else
      parseError("Missing '='");
  }
  else if (scanner->token->getInformation()->equals("print")) {
    scanner->nextToken();

    if (scanner->token->getInformation()->getType() == TTYPE_R_B_O) {
      scanner->nextToken();
      exp = new ExpNEW(scanner, out, pE, tE);

      if (scanner->token->getInformation()->getType() == TTYPE_R_B_C) {
        statementType = STATEMENT_PRINT;
        scanner->nextToken();
      }
      else
        parseError("Missing ')'");
    }
    else
      parseError("Missing '('");
  }
  else if (scanner->token->getInformation()->equals("read")) {
    scanner->nextToken();

    if (scanner->token->getInformation()->getType() == TTYPE_R_B_O) {
      scanner->nextToken();

      if (scanner->token->getInformation()->getType() == TTYPE_CONFIRMED_IDENTIFIER) {
        info = scanner->token->getInformation();
        scanner->nextToken();
        index = new IndexNEW(scanner, out, pE, tE);

        if (scanner->token->getInformation()->getType() == TTYPE_R_B_C) {
          statementType = STATEMENT_READ;
          scanner->nextToken();
        }
        else
          parseError("Missing ')'");
      }
      else
        parseError("Identifier expected");
    }
    else
      parseError("Missing '('");
  }
  else if (scanner->token->getInformation()->equals("if")) {
    scanner->nextToken();

    if (scanner->token->getInformation()->getType() == TTYPE_R_B_O) {
      scanner->nextToken();
      exp = new ExpNEW(scanner, out, pE, tE);

      if (scanner->token->getInformation()->getType() == TTYPE_R_B_C) {
          scanner->nextToken();

          // In case "{" comes we assume that multiple statements are in the if-block
//          if(scanner->token->getInformation()->getType() == TTYPE_C_B_O)
//            statements1 = new StatementsNEW(scanner, out, pE, tE);  // if-block with one or multiple statements
//          else
            statement1 = new StatementNEW(scanner, out, pE, tE); // if-block with a single statement

          if(scanner->token->getInformation()->equals("else")) {
              scanner->nextToken();

              // In case "{" comes we assume that multiple statements are in the else-block
//              if(scanner->token->getInformation()->getType() == TTYPE_C_B_O)
//                statements2 = new StatementsNEW(scanner, out, pE, tE);  // else-block with one or multiple statements
//              else
                statement2 = new StatementNEW(scanner, out, pE, tE); // else-block with a single statement

              statementType = STATEMENT_IF_ELSE;
          }
          else
            parseError("Missing 'else'");
      }
      else
        parseError("Missing ')'");
    }
    else
      parseError("Missing '('");
  }
  else if (scanner->token->getInformation()->equals("while")) {
    scanner->nextToken();

    if (scanner->token->getInformation()->getType() == TTYPE_R_B_O) {
      scanner->nextToken();
      exp = new ExpNEW(scanner, out, pE, tE);

      if (scanner->token->getInformation()->getType() == TTYPE_R_B_C) {
          scanner->nextToken();
          statement1 = new StatementNEW(scanner, out, pE, tE);
          statementType = STATEMENT_WHILE;
      }
      else
        parseError("Missing ')'");
    }
    else
      parseError("Missing '('");
  }
  else if(scanner->token->getInformation()->getType() == TTYPE_C_B_O) {
      scanner->nextToken();
      statements = new StatementsNEW(scanner, out, pE, tE);

      if(scanner->token->getInformation()->getType() == TTYPE_C_B_C) {
        scanner->nextToken();
        statementType = STATEMENT_BLOCK;
      }
      else
        parseError("Missing '}'");
  }
  else
    parseError("Expected 'print', 'read', 'if', 'while', '{' or an identifier.");
}

StatementNEW::~StatementNEW() {
  if(!statement1)
    delete statement1;
//  if(!statements1)
//    delete statements1;
  if(!statement2)
    delete statement2;
  if(!statements)
    delete statements;
//  if(!statements2)
//    delete statements2;
//  if(statements->getSize())
//    delete statements;
}

void StatementNEW::typeCheck() {
  nodeType = ERROR_TYPE;

  switch (statementType) {
    case STATEMENT_ASSIGN: // identifier INDEX = EXP
      exp->typeCheck();
      index->typeCheck();

      if ((exp->nodeType == INT_TYPE || exp->nodeType == ARRAY_TYPE)  &&
         ((info->getType() == TTYPE_CONFIRMED_IDENTIFIER && index->nodeType == NO_TYPE) || (info->getType() == TTYPE_ARRAY && index->nodeType == ARRAY_TYPE)))
        nodeType = NO_TYPE;
      else
        typeError("Incompatible types");
      break;
    case STATEMENT_PRINT: // print (EXP)
      exp->typeCheck();
      nodeType = NO_TYPE;
      break;
    case STATEMENT_READ: // read (identifier INDEX)
      index->typeCheck();

      if ((info->getType() == TTYPE_CONFIRMED_IDENTIFIER && index->nodeType == NO_TYPE) || (info->getType() == TTYPE_ARRAY && index->nodeType == ARRAY_TYPE))
        nodeType = NO_TYPE;
      else
        typeError("incompatible types");
      break;
    case STATEMENT_BLOCK: // {STATEMENTS}
      statements->typeCheck();
      nodeType = NO_TYPE;
      break;
    case STATEMENT_IF_ELSE: // if...
      exp->typeCheck();
      statement1->typeCheck();
      statement2->typeCheck();

      if (exp->nodeType == ERROR_TYPE)
        nodeType = ERROR_TYPE;
      else
        nodeType = NO_TYPE;
      break;
    case STATEMENT_WHILE: //while...
      exp->typeCheck();
      statement1->typeCheck();

      if (exp->nodeType == ERROR_TYPE)
        nodeType = ERROR_TYPE;
      else
        nodeType = NO_TYPE;
      break;
    default:
      nodeType = ERROR_TYPE;
      typeError("Identifier not defined");
      break;
  }
}

void StatementNEW::makeCode(OutBuffer *out) {
  int M1;
  int M2;

  switch (statementType) {
    case STATEMENT_ASSIGN: //identifier
      exp->makeCode(out);
      (*out) << "LA $" << info->getLexem() << "\n";
      index->makeCode(out);
      (*out) << "STR\n";
      break;
    case STATEMENT_PRINT: //print
      exp->makeCode(out);
      (*out) << "PRI\n";
      break;
    case STATEMENT_READ: //read
      (*out) << "REA\n" << "LA $" << info->getLexem() << "\n";
      index->makeCode(out);
      (*out) << "STR\n";
      break;
    case STATEMENT_BLOCK: //{...}
      statements->makeCode(out);
      break;
    case STATEMENT_IF_ELSE: // if ...
      M1 = mark++;
      M2 = mark++;
      exp->makeCode(out);
      (*out) << "JIN #M" << M1 << "\n";
      statement1->makeCode(out);
      (*out) << "JMP #M" << M2
             << "\n#M" << M1 << " NOP\n";
      statement2->makeCode(out);
      (*out) << "#M" << M2 << " NOP\n";
      break;
    case STATEMENT_WHILE: // while // FIXME: See case 4
      M1 = mark++;
      M2 = mark++;
      (*out) << "#M" << M1 << " NOP\n";
      exp->makeCode(out);
      (*out) << "JIN #M" << M2 << "\n";
      statement1->makeCode(out);
      (*out) << "JMP #M" << M1 << "\n#M" << M2 << " NOP\n";
      break;
  }
}

ExpNEW::ExpNEW(Scanner* scanner, OutBuffer* out, int& pE, int &tE) : Node(scanner) {
  exp2 = new Exp2NEW(scanner, out, pE, tE);
  op_exp = new Op_expNEW(scanner, out, pE, tE);
}

ExpNEW::~ExpNEW() {
  if(!exp2)
    delete exp2;
  if(!op_exp)
    delete op_exp;
}

void ExpNEW::typeCheck() {
  exp2->typeCheck();
  op_exp->typeCheck();

  if (op_exp->nodeType == NO_TYPE)
    nodeType = exp2->nodeType;
  else if (exp2->nodeType != op_exp->nodeType)
    nodeType = ERROR_TYPE;
  else
    nodeType = exp2->nodeType;
}

void ExpNEW::makeCode(OutBuffer *out) {
  if (op_exp->nodeType == NO_TYPE)
    exp2->makeCode(out);
  else if (op_exp->nodeType == OP_GREATER_TYPE) {
    op_exp->makeCode(out);
    exp2->makeCode(out);
    (*out) << "LES\n";  // FIXED: was LESS
  }
  else if (op_exp->nodeType == OP_AEQUI_TYPE) { // FIXME: this type is never assigned!
    exp2->makeCode(out);
    op_exp->makeCode(out);
    (*out) << "NOT\n";	// this handles the ! and the <=> (check if this should be handled like this!) Note: currently there is no OP_AEQU_TYPE!!!
  }
  else {
    exp2->makeCode(out);
    op_exp->makeCode(out);
  }
}

Exp2NEW::Exp2NEW(Scanner* scanner, OutBuffer* out, int& pE, int &tE) : Node(scanner) {
  expressionType = 0;
  exp = 0;
  exp2 = 0;
  index = 0;

  if (scanner->token->getInformation()->getType() == TTYPE_R_B_O) {
    scanner->nextToken();
    exp = new ExpNEW(scanner, out, pE, tE);

    if (scanner->token->getInformation()->getType() == TTYPE_R_B_C) {
      expressionType = EXPRESSION_BRACKETS;
      scanner->nextToken();
    } else
      parseError("Missing ')'");
  }
  else if (scanner->token->getInformation()->getType() == TTYPE_CONFIRMED_IDENTIFIER || scanner->token->getInformation()->getType() == TTYPE_ARRAY) {
    expressionType = EXPRESSION_IDENTIFIER;
    scanner->nextToken();
    index = new IndexNEW(scanner, out, pE, tE);
  }
  else if (scanner->token->getInformation()->getType() == TTYPE_INT) {
    expressionType = EXPRESSION_INT;
    value = scanner->token->getValue();
    scanner->nextToken();
  }
  else if (scanner->token->getInformation()->getType() == TTYPE_MINUS) {
    expressionType = EXPRESSION_NEGATIVE;
    scanner->nextToken();
    exp2 = new Exp2NEW(scanner, out, pE, tE);
  }
  else if (scanner->token->getInformation()->getType() == TTYPE_NOT) { // FIXME: was TTYPE_EXCL_M
    expressionType = EXPRESSION_NOT;
    cout << "TYPECHECK() -- NOT EQUALS TOKEN" << endl;
    scanner->nextToken();
    exp2 = new Exp2NEW(scanner, out, pE, tE);
  }
  else
    parseError("Expected '(', '-', '!', an identifier or an integer value");
}

Exp2NEW::~Exp2NEW() {
  if(!exp)
    delete exp;
  if(!exp2)
    delete exp2;
  if(!index)
    delete index;
}

void Exp2NEW::typeCheck() {
  switch (expressionType) {
    case EXPRESSION_BRACKETS: // (exp)
      exp->typeCheck();
      nodeType = exp->nodeType;
      break;
    case EXPRESSION_IDENTIFIER: // identifier INDEX
      index->typeCheck();
      //      if ((info->getType() == TTYPE_CONFIRMED_IDENTIFIER || info->getType() == TTYPE_ARRAY) && index->nTermType == NO_TYPE)

      if (info->getType() == TTYPE_CONFIRMED_IDENTIFIER && index->nodeType == NO_TYPE)
        nodeType = INT_TYPE;
      else if (info->getType() == TTYPE_ARRAY && index->nodeType == ARRAY_TYPE)
        nodeType = ARRAY_TYPE;
      else
        typeError("Expected a primitive type");
      break;
    case EXPRESSION_INT: // integer
      nodeType = INT_TYPE;
      break;
    case EXPRESSION_NEGATIVE: //- Exp2
      exp2->typeCheck();
      nodeType = exp2->nodeType;
      break;
    case EXPRESSION_NOT: // !exp2
      exp2->typeCheck();

      if (exp2->nodeType == INT_TYPE)
        nodeType = INT_TYPE;
      else
        typeError("Expected an integer");
  }
}

void Exp2NEW::makeCode(OutBuffer *out) {
  switch (expressionType) {
    case EXPRESSION_BRACKETS: // (exp)
      exp->makeCode(out);
      break;
    case EXPRESSION_IDENTIFIER: // identifier INDEX
      (*out) << "LA $" << info->getLexem() << "\n";
      index->makeCode(out);
      (*out) << "LV\n";
      break;
    case EXPRESSION_INT: // integer
      (*out) << "LC " << value << "\n";
      break;
    case EXPRESSION_NEGATIVE: // -Exp2
      (*out) << "LC " << 0 << "\n";
      exp2->makeCode(out);
      (*out) << "SUB\n";
      break;
    case EXPRESSION_NOT: // !exp2
      exp2->makeCode(out);
      (*out) << "NOT\n";
  }
}

Op_expNEW::Op_expNEW(Scanner* scanner, OutBuffer* out, int& pE, int &tE) : Node(scanner) {
  op = 0;
  exp = 0;

  if (scanner->token->getInformation()->getType() >= TTYPE_PLUS && scanner->token->getInformation()->getType() <= TTYPE_AMP) {
    op = new OpNEW(scanner, out, pE, tE);
    exp = new ExpNEW(scanner, out, pE, tE);
  }
}

Op_expNEW::~Op_expNEW() {
  if (op)
    delete op;
  if (exp)
    delete exp;
}

void Op_expNEW::typeCheck() {
  if (op) {
    op->typeCheck();
    exp->typeCheck();
    nodeType = exp->nodeType;
  }
  else
    nodeType = NO_TYPE;
}

void Op_expNEW::makeCode(OutBuffer *out) {
  if (op && exp) {
    exp->makeCode(out);
    op->makeCode(out);
  }
}

OpNEW::OpNEW(Scanner* scanner, OutBuffer* out, int& pE, int &tE) : Node(scanner) {
  info = scanner->token->getInformation();
  scanner->nextToken();
}

OpNEW::~OpNEW() {}

void OpNEW::typeCheck() {
//  nodeType = info->getType();

  switch (info->getType()) {
    case TTYPE_PLUS:
      nodeType = OP_PLUS_TYPE;
      break;
    case TTYPE_MINUS:
      nodeType = OP_MINUS_TYPE;
      break;
    case TTYPE_MULT:
      nodeType = OP_MULT_TYPE;
      break;
    case TTYPE_DIV:
      nodeType = OP_DIV_TYPE;
      break;
    case TTYPE_GREATER:
      nodeType = OP_GREATER_TYPE;
      break;
    case TTYPE_LESS:
      nodeType = OP_LESS_TYPE;
      break;
    case TTYPE_EQUALS:
      nodeType = OP_EQUAL_TYPE;
      break;
    case TTYPE_AEQUI:
      nodeType = OP_AEQUI_TYPE;
      break;
    case TTYPE_AMP:
      nodeType = OP_AND_TYPE;
      break;
    case TTYPE_NOT:
      nodeType = OP_NOT_TYPE;
  }
}

void OpNEW::makeCode(OutBuffer *out) {
    switch (nodeType) {
      case OP_PLUS_TYPE:
        (*out) << "ADD\n";
        break;
      case OP_MINUS_TYPE:
        (*out) << "SUB\n";
        break;
      case OP_MULT_TYPE:
        (*out) << "MUL\n";
        break;
      case OP_DIV_TYPE:
        (*out) << "DIV\n";
        break;
      case OP_GREATER_TYPE:
        cout << "> SIGN" << endl;
  //      (*out) << "----TTYPE_GREATER----\n";
//        (*out) << "LES\nNOT\n";
        (*out) << "LES\nNOT\n"; // FIX: partial fix for greater operator; this is not how it's described in the PDF documentation
        break;
      case OP_LESS_TYPE:
        (*out) << "LES\n";
        break;
      case OP_EQUAL_TYPE:
        (*out) << "EQU\n";
        break;
      case OP_NOT_TYPE:	// FIXME: this should be in EXP2 and Exp since the "!" is handled there (OR NOT?! Think about it)
        (*out) << "NOT\n";
        break;
      case OP_AEQUI_TYPE:
        cout << "<=> SIGN" << endl;
  //      (*out) << "----TTYPE_AEQUI----\n";
//        (*out) << "EQU\n";
        (*out) << "EQU\nNOT\n"; //FIX: added "NOT\n"; REASON: combined with NOT - FIXME: when debugging <=> we come here without the NOT so it is evaluated as =
        break;
      case OP_AND_TYPE:
        (*out) << "AND\n";
        break;
    }
//  switch (info->getType()) {
//    case TTYPE_PLUS:
//      (*out) << "ADD\n";
//      break;
//    case TTYPE_MINUS:
//      (*out) << "SUB\n";
//      break;
//    case TTYPE_MULT:
//      (*out) << "MUL\n";
//      break;
//    case TTYPE_DIV:
//      (*out) << "DIV\n";
//      break;
//    case TTYPE_GREATER:
//      cout << "> SIGN" << endl;
////      (*out) << "----TTYPE_GREATER----\n";
//      (*out) << "LES\nNOT\n"; // FIX: partial fix for greater operator; this is not how it's described in the PDF documentation
//      break;
//    case TTYPE_LESS:
//      (*out) << "LES\n";
//      break;
//    case TTYPE_EQUALS:
//      (*out) << "EQU\n";
//      break;
//    case TTYPE_NOT:	// FIXME: this should be in EXP2 and Exp since the "!" is handled there (OR NOT?! Think about it)
//      (*out) << "NOT\n";
//      break;
//    case TTYPE_AEQUI:
//      cout << "<=> SIGN" << endl;
////      (*out) << "----TTYPE_AEQUI----\n";
//      (*out) << "EQU\nNOT\n"; //FIX: added "NOT\n"; REASON: combined with NOT - FIXME: when debugging <=> we come here without the NOT so it is evaluated as =
//      break;
//    case TTYPE_AMP:
//      (*out) << "AND\n";
//      break;
//  }
}
