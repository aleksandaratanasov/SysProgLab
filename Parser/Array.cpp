#include "Array.h"

#include "../Scanner/Token.h"
#include "../Scanner/t_const.h"
#include "../Scanner/Information.h"
#include "../Scanner/Scanner.h"
#include "../IO/OutBuffer.h"

Array::Array(Scanner* scanner, OutBuffer* out):Nterm(scanner) {
   UP
   if (scanner->token->getInformation()->getType() == TTYPE_S_B_O) {
    value = -1;
    scanner->nextToken();
    if (scanner->token->getInformation()->getType() == TTYPE_INT) {
      value = scanner->token->getValue();
      scanner->nextToken();
      if (scanner->token->getInformation()->getType() == TTYPE_S_B_C) {
        scanner->newIdentifier();
        nTermType = ARRAY_TYPE;
      } else 
        parseError("Missing closing ']'");
    } else
      parseError("Integer Value expected");
  } else { 
      PROGRESS("€ array")
      nTermType = NO_TYPE;
  }
  DOWN
}

void Array::typeCheck() {
  UP
  PROGRESS_T("array (Dim = " << value << ") ")
  if(nTermType == ARRAY_TYPE && value < 1) {
    typeError("No valid dimension");
    nTermType = ERROR_TYPE;
  }
  DOWN
}

void Array::makeCode(OutBuffer* out) {
  if (nTermType == ARRAY_TYPE)
    (*out) << " " << value << "\n";
  else
    (*out) << " " << 1 << "\n";
}

Array::~Array() {
}
