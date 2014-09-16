#include "Nterm.h"
#include <iostream>
#include <typeinfo> 

#include "../Scanner/Scanner.h"
#include "../Scanner/Token.h"
#include "../Scanner/Information.h"
#include "../IO/OutBuffer.h"

using std::cout;
using std::endl;
using std::cerr;

Nterm::Nterm(Scanner* scanner) {
  this->scanner = scanner;
  cloneTokenData();
}

void Nterm::cloneTokenData() {
  line = scanner->token->getLine();
  column = scanner->token->getColumn();
  value = scanner->token->getValue();
  info = scanner->token->getInformation();
}

void Nterm::parseError(const char* message) {
  cout << "Parse error at [" << line << ":" << column << "] (" << info->getLexem() <<  ") :"  << message  << endl;
  nTermType = ERROR_TYPE;
  parseErrors++;
}

void Nterm::typeError(const char* message) {
  cout << "Type error at [" << line << ":" << column << "] (" << info->getLexem() <<  ") :"  << message  << endl;
  nTermType = ERROR_TYPE;
  typeErrors++;
}


Nterm::~Nterm() {}

int Nterm::mark = 1;
unsigned int Nterm::entry = 0;
unsigned int Nterm::parseErrors = 0;
unsigned int Nterm::typeErrors = 0;
