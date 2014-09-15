#include "Decl.h"
#include "Array.h"

#include "Nterm.h"
#include "../Scanner/t_const.h"

Decl::Decl(Scanner* scanner, OutBuffer* out):Nterm(scanner) {
  UP
  PROGRESS("Decl->Array")
  array = new Array(scanner, out);
  if (scanner->token->getInformation()->getType() == TTYPE_CONFIRMED_IDENTIFIER) {
    info = scanner->token->getInformation();
    scanner->nextToken();
  } else 
    parseError("Error: new Identifier expected");
  DOWN
}

void Decl::typeCheck() {
  UP
  PROGRESS_T("decl")
  array->typeCheck();
  if (scanner->token->getInformation()->getType() == TTYPE_EXISTING_IDENTIFIER) {
    typeError("identifer already defined");
    nTermType = ERROR_TYPE;
  } else if (array->nTermType == ERROR_TYPE) {
    nTermType = ERROR_TYPE;
  } else {
    nTermType = NO_TYPE;
    if (array->nTermType == ARRAY_TYPE) 
      info->toArray();
  }
  DOWN
}

void Decl::makeCode(OutBuffer* out) {
  PROGRESS_M("Decl");
  (*out) << "DS $" << info->getLexem();
  array->makeCode(out);
  PROGRESS_M("Decl €");
}

Decl::~Decl() {
  delete array;
}