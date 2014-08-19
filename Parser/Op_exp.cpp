#include "Op_exp.h"
#include "Op.h"
#include "Exp.h"
#include "../Scanner/Scanner.h"

#include "Nterm.h"


Op_exp::Op_exp(Scanner* scanner, OutBuffer* out):Nterm(scanner) {
  UP
  op = 0;
  exp = 0;
/*  if (scanner->token->getInformation()->equals("+") ||
      scanner->token->getInformation()->equals("-") ||
      scanner->token->getInformation()->equals("*") ||
      scanner->token->getInformation()->equals("/") ||
      scanner->token->getInformation()->equals(">") ||
      scanner->token->getInformation()->equals("<") ||
      scanner->token->getInformation()->equals("=") ||
      scanner->token->getInformation()->equals("<=>") ||
      scanner->token->getInformation()->equals("&")) {*/
  if (scanner->token->getInformation()->getType() >= TTYPE_PLUS && scanner->token->getInformation()->getType() <= TTYPE_AMP) {
    PROGRESS("op_exp->op");
    op = new Op(scanner, out);
    PROGRESS("op_exp->exp");
    exp = new Exp(scanner, out);
  }
  else {
    PROGRESS("€ op_exp")
    op = 0;
  }
  DOWN
}

void Op_exp::typeCheck() {
  UP
  PROGRESS_T("op_exp")
  if (op != 0) {
    op->typeCheck();
    exp->typeCheck();
    nTermType = exp->nTermType;
  } else
    nTermType = NO_TYPE;
  DOWN  
}

void Op_exp::makeCode(OutBuffer* out) {
  PROGRESS_M("Op_exp");
  if (op != 0 && exp != 0) {
    exp->makeCode(out);
    op->makeCode(out);
  }
}

Op_exp::~Op_exp() {
  if (op != 0)
    delete op;
  if (exp != 0) 
    delete exp;
}