#include "Nterm.h"
#include <iostream>
#include <typeinfo> 

#include "../Scanner/Scanner.h"
#include "../Scanner/Token.h"
#include "../Scanner/Information.h"
#include "../IO/OutBuffer.h"


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
  std::cout << "Parse Error at " << line << "/" << column << " (" << info->getLexem() <<  ") :"  << message  << std::endl;
  nTermType = ERROR_TYPE;
  parseErrors++;
}

void Nterm::typeError(const char* message) {
  std::cout << "Type Error at " << line << "/" << column << " (" << info->getLexem() <<  ") :"  << message  << std::endl;
  nTermType = ERROR_TYPE;
  typeErrors++;
}


Nterm::~Nterm() {}

int Nterm::marke = 1;
unsigned int Nterm::entry = 0;
unsigned int Nterm::parseErrors = 0;
unsigned int Nterm::typeErrors = 0;
