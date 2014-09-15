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

  end = clock();
  std::cout << "Parsing complete" << std::endl << "Used time: "  << (double)(end-start)/CLOCKS_PER_SEC << " s" << std::endl;
}

ParserNEW::~ParserNEW() {
  //TODO - delete everything the parser has dumped into memory
}

Node::Node(Scanner* scanner) {

}

Node::~Node() {}

int ProgNEW::i = 0;

ProgNEW::ProgNEW(Scanner* scanner, OutBuffer* out, int& pE, int &tE) : Node(scanner) {
  i++;
  std::cout << "I = " << i << std::endl;
  decls = new DeclsNEW(scanner, out, pE, tE);
  delete decls;
  statements = new StatementsNEW(scanner, out, pE, tE);
  delete statements;
}

ProgNEW::~ProgNEW() {}

void ProgNEW::typeCheck() {
}

void ProgNEW::makeCode(OutBuffer *out) {
}

DeclsNEW::DeclsNEW(Scanner* scanner, OutBuffer* out, int& pE, int &tE) : Node(scanner) {
//  while("int" encountered) {
//     goto Decl
//  }
}

DeclsNEW::~DeclsNEW() {
  // delete each element in the ListT
}

void DeclsNEW::typeCheck() {

}

void DeclsNEW::makeCode(OutBuffer *out) {

}

DeclNEW::DeclNEW(Scanner* scanner, OutBuffer* out, int& pE, int &tE) : Node(scanner) {

}

DeclNEW::~DeclNEW() {}

void DeclNEW::typeCheck() {

}

void DeclNEW::makeCode(OutBuffer *out) {

}

ArrayNEW::ArrayNEW(Scanner* scanner, OutBuffer* out, int& pE, int &tE) : Node(scanner) {

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
