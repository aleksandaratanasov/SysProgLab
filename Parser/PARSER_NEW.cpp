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
  delete decls;
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

IndexNEW::~IndexNEW() {}

void IndexNEW::typeCheck() {

}

void IndexNEW::makeCode(OutBuffer *out) {

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
  if(statements->getSize())
    delete statements;
}

void StatementsNEW::typeCheck() {

}

void StatementsNEW::makeCode(OutBuffer *out) {

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
        parseError("Missing closing ')'");
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
          parseError("Missing closing ')'");
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

}

void StatementNEW::makeCode(OutBuffer *out) {

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

}

void ExpNEW::makeCode(OutBuffer *out) {

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
  else if (scanner->token->getInformation()->getType() == TTYPE_N_EQUALS) { // FIXME: was TTYPE_EXCL_M
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

      if ((info->getType() == TTYPE_CONFIRMED_IDENTIFIER) && index->nodeType == NO_TYPE) {
        nodeType = INT_TYPE;
      }
      else if (info->getType() == TTYPE_ARRAY && index->nodeType == ARRAY_TYPE) {
        nodeType = ARRAY_TYPE;
      }
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
  if (!op)
    delete op;
  if (!exp)
    delete exp;
}

void Op_expNEW::typeCheck() {
  if (op != 0) {
    op->typeCheck();
    exp->typeCheck();
    nodeType = exp->nodeType;
  }
  else
    nodeType = NO_TYPE;
}

void Op_expNEW::makeCode(OutBuffer *out) {

}

OpNEW::OpNEW(Scanner* scanner, OutBuffer* out, int& pE, int &tE) : Node(scanner) {
  info = scanner->token->getInformation();
  scanner->nextToken();
}

OpNEW::~OpNEW() {}

void OpNEW::typeCheck() {
  nodeType = info->getType();
}

void OpNEW::makeCode(OutBuffer *out) {
  switch (info->getType()) {
    case TTYPE_PLUS:
      (*out) << "ADD\n";
      break;
    case TTYPE_MINUS:
      (*out) << "SUB\n";
      break;
    case TTYPE_MULT:
      (*out) << "MUL\n";
      break;
    case TTYPE_DIV:
      (*out) << "DIV\n";
      break;
    case TTYPE_GREATER:
      cout << "> SIGN" << endl;
//      (*out) << "LES\nNOT\n"; // FIX: partial fix for greater operator; this is not how it's described in the PDF documentation
      break;
    case TTYPE_LESS:
      (*out) << "LES\n";
      break;
    case TTYPE_EQUALS:
      (*out) << "EQU\n";
      break;
    case TTYPE_N_EQUALS:	// FIXME: this should be in EXP2 and Exp since the "!" is handled there (OR NOT?! Think about it)
      (*out) << "NOT\n";
      break;
    case TTYPE_AEQUI:
      cout << "<=> SIGN" << endl;
      //(*out) << "EQU\nNOT\n"; //FIX: added "NOT\n"; REASON: combined with NOT - FIXME: when debugging <=> we come here without the NOT so it is evaluated as =
      break;
    case TTYPE_AMP:
      (*out) << "AND\n";
      break;
  }
}
