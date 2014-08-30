#include "Exp2.h"
#include "Index.h"
#include "Exp.h"
#include "../Scanner/Scanner.h"

#include "../Scanner/Token.h"
#include "../Scanner/t_const.h"
#include "../Scanner/Information.h"
#include "../Scanner/Scanner.h"
#include "../IO/OutBuffer.h"


Exp2::Exp2(Scanner* scanner, OutBuffer* out):Nterm(scanner) {
  UP
  type = 0;
  exp = 0;
  exp2 = 0;
  index = 0;
  if (scanner->token->getInformation()->getType() == TTYPE_R_B_O) {
    PROGRESS("exp2->exp");
    scanner->nextToken();
    exp = new Exp(scanner, out);
    if (scanner->token->getInformation()->getType() == TTYPE_R_B_C) {
      type = 1;
      scanner->nextToken();
    } else
      parseError("Missing ')'");
  }
  else if (scanner->token->getInformation()->getType() == TTYPE_CONFIRMED_IDENTIFIER || scanner->token->getInformation()->getType() == TTYPE_ARRAY) {
    type = 2;
    PROGRESS("exp2->index");
    scanner->nextToken();
    index = new Index(scanner, out);
  }
  else if (scanner->token->getInformation()->getType() == TTYPE_INT) {
    type = 3;
    value = scanner->token->getValue();
    scanner->nextToken();
  }
  else if (scanner->token->getInformation()->getType() == TTYPE_MINUS) {
    type = 4;
    PROGRESS("exp2->exp2");
    scanner->nextToken();
    exp2 = new Exp2(scanner, out);
  }
  else if (scanner->token->getInformation()->getType() == TTYPE_N_EQUALS) { // FIXME: was TTYPE_EXCL_M
    type = 5;
    std::cout << "TYPECHECK() -- NOT EQUALS TOKEN" << std::endl;
    PROGRESS("exp2->exp2");
    scanner->nextToken();
    exp2 = new Exp2(scanner, out);
  }
  else {
    parseError("Expected '(', '-', '!', an identifier or an integer value");
  }
  DOWN
}

void Exp2::typeCheck() {
  UP
  PROGRESS_T("exp2")
  switch (type) {
    case 1: // (exp)
      exp->typeCheck();
      nTermType = exp->nTermType;
      break;
    case 2: // identifier INDEX
      index->typeCheck();
      //      if ((info->getType() == TTYPE_CONFIRMED_IDENTIFIER || info->getType() == TTYPE_ARRAY) && index->nTermType == NO_TYPE)
      if ((info->getType() == TTYPE_CONFIRMED_IDENTIFIER) && index->nTermType == NO_TYPE) {
        nTermType = INT_TYPE;
        std::cout << "int" << std::endl;
      }
      else if (info->getType() == TTYPE_ARRAY && index->nTermType == ARRAY_TYPE) {
	nTermType = ARRAY_TYPE;
	std::cout << "ARRAY" << std::endl;
      }
      else
	typeError("no primitive type");
      break;
    case 3: // integer
      nTermType = INT_TYPE;
      std::cout << "int" << std::endl;
      break;
    case 4: //- Exp2
      exp2->typeCheck();
      nTermType = exp2->nTermType;
      break;
    case 5: // !exp2
      exp2->typeCheck();
      if (exp2->nTermType == INT_TYPE)
	nTermType = INT_TYPE;
      else
	typeError("not an integer");

  }
  DOWN
}

void Exp2::makeCode(OutBuffer* out) {
  PROGRESS_M("Exp2");
  switch (type) {
    case 1: // (exp)
	exp->makeCode(out);
	break;
    case 2: // identifier INDEX
      (*out) << "LA $" << info->getLexem() << "\n";
      index->makeCode(out);
      (*out) << "LV\n";
      break;
    case 3: // integer
      (*out) << "LC " << value << "\n";
      break;
    case 4: // -Exp2
      (*out) << "LC " << 0 << "\n";
      exp2->makeCode(out);
      (*out) << "SUB\n";
      break;
    case 5: // !exp2
      exp2->makeCode(out);
      (*out) << "NOT\n";
      break;
  }
}

Exp2::~Exp2() {
  if (exp != 0)
    delete exp;
  if (exp2 != 0)
    delete exp2;
  if (index != 0)
    delete index;
}
