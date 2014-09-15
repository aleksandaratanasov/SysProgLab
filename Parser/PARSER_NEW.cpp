#include "PARSER_NEW.h"
#include "../Scanner/Scanner.h"
#include <iostream>
#include <time.h> // For measuring the compilation time

ParserNEW::ParserNEW(Scanner *scanner, OutBuffer *out) {
  clock_t start, end;
  int typeErrors, parseErrors;
  start = clock();

  scanner->nextToken();
  std::cout << "Starting parsing..." << std::endl;

  ProgNEW *prog = new ProgNEW(scanner, out, parseErrors, typeErrors);
  delete prog;

  end = clock();
  std::cout << "Parsing complete" << std::endl << "Used time: "  << (double)(end-start)/CLOCKS_PER_SEC << " s" << std::endl;
}

ParserNEW::~ParserNEW() {
  //TODO - delete everything the parser has dumped into memory
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
  std::cout << "Parse error at [" << line << ":" << column << "] (" << info->getLexem() <<  ") :"  << message  << std::endl;
  nodeType = ERROR_TYPE;
  parseErrors++;
}

void Node::typeError(const char* message) {
  std::cout << "Type error at [" << line << ":" << column << "] (" << info->getLexem() <<  ") :"  << message  << std::endl;
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
}

void ProgNEW::makeCode(OutBuffer *out) {
}

DeclsNEW::DeclsNEW(Scanner* scanner, OutBuffer* out, int& pE, int &tE) : Node(scanner) {
//  while("int" encountered) {
//     goto Decl
//  }
  decls = new ListT<DeclNEW>();

  while(scanner->token->getInformation()->equals("int")) {
    scanner->newIdentifier();
//    DeclNEW *decl = new DeclNEW(scanner, out, pE, tE);
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
  // delete each element in the ListT
  delete decls;
}

void DeclsNEW::typeCheck() {
  ListTElement<DeclNEW>* tmp = decls->first;
  while (tmp) {
    tmp->getData()->typeCheck(); // check type of each decl in the list of decls
    tmp = tmp->getNext();
  }
}

void DeclsNEW::makeCode(OutBuffer *out) {

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

DeclNEW::~DeclNEW() {}

void DeclNEW::typeCheck() {

}

void DeclNEW::makeCode(OutBuffer *out) {

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
    nodeType = NO_TYPE;
}

ArrayNEW::~ArrayNEW() {}

void ArrayNEW::typeCheck() {

}

void ArrayNEW::makeCode(OutBuffer *out) {

}

IndexNEW::IndexNEW(Scanner* scanner, OutBuffer* out, int& pE, int &tE) : Node(scanner) {

}

IndexNEW::~IndexNEW() {}

void IndexNEW::typeCheck() {

}

void IndexNEW::makeCode(OutBuffer *out) {

}

StatementsNEW::StatementsNEW(Scanner* scanner, OutBuffer* out, int& pE, int &tE) : Node(scanner) {

}

StatementsNEW::~StatementsNEW() {
  // delete each element in the ListT
}

void StatementsNEW::typeCheck() {

}

void StatementsNEW::makeCode(OutBuffer *out) {

}

StatementNEW::StatementNEW(Scanner* scanner, OutBuffer* out, int& pE, int &tE) : Node(scanner) {

}

StatementNEW::~StatementNEW() {}

void StatementNEW::typeCheck() {

}

void StatementNEW::makeCode(OutBuffer *out) {

}

ExpNEW::ExpNEW(Scanner* scanner, OutBuffer* out, int& pE, int &tE) : Node(scanner) {

}

ExpNEW::~ExpNEW() {}

void ExpNEW::typeCheck() {

}

void ExpNEW::makeCode(OutBuffer *out) {

}

Exp2NEW::Exp2NEW(Scanner* scanner, OutBuffer* out, int& pE, int &tE) : Node(scanner) {

}

Exp2NEW::~Exp2NEW() {}

void Exp2NEW::typeCheck() {

}

void Exp2NEW::makeCode(OutBuffer *out) {

}

Op_expNEW::Op_expNEW(Scanner* scanner, OutBuffer* out, int& pE, int &tE) : Node(scanner) {

}

Op_expNEW::~Op_expNEW() {}

void Op_expNEW::typeCheck() {

}

void Op_expNEW::makeCode(OutBuffer *out) {

}

OpNEW::OpNEW(Scanner* scanner, OutBuffer* out, int& pE, int &tE) : Node(scanner) {

}

OpNEW::~OpNEW() {}

void OpNEW::typeCheck() {

}

void OpNEW::makeCode(OutBuffer *out) {

}
