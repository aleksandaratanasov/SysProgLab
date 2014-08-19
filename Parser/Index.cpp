#include "Index.h"
#include "Exp.h"
#include "../Scanner/Scanner.h"

#include "../Scanner/Token.h"
#include "../Scanner/t_const.h"
#include "../Scanner/Information.h"
#include "../Scanner/Scanner.h"
#include "../IO/OutBuffer.h"


Index::Index(Scanner* scanner, OutBuffer* out):Nterm(scanner) {
  UP
  exp = 0;
  //if (scanner->token->getInformation()->equals("[")) {
  if (scanner->token->getInformation()->getType() == TTYPE_S_B_O) {
      PROGRESS("index->exp");
    scanner->nextToken();
    exp = new Exp(scanner, out);
    if (scanner->token->getInformation()->getType() == TTYPE_S_B_C)
	scanner->nextToken();
    else 
      parseError("Missing closing ']'");
  } else {
    PROGRESS("€ index")
    exp = 0;
  }
  DOWN
}

void Index::typeCheck() {
  UP
  PROGRESS_T("index")
  if (exp != 0) {
    exp->typeCheck();
    if (exp->nTermType == ERROR_TYPE)
      nTermType = ERROR_TYPE;
    else
      nTermType = ARRAY_TYPE;
  } else
    nTermType = NO_TYPE;
   DOWN 
}

void Index::makeCode(OutBuffer* out) {
  PROGRESS_M("Index");
  if (exp != 0) {
    exp->makeCode(out);
    (*out) << "ADD\n";
  } 
}

Index::~Index(){
  if (exp != 0)
    delete exp;
}
    