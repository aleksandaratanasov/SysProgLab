#include "Exp.h"
#include "Exp2.h"
#include "Op_exp.h"
#include "../Scanner/Scanner.h"

#include "../Scanner/Token.h"
#include "../Scanner/t_const.h"
#include "../Scanner/Information.h"
#include "../Scanner/Scanner.h"
#include "../IO/OutBuffer.h"


Exp::Exp(Scanner* scanner, OutBuffer* out):Nterm(scanner) {
  UP
  PROGRESS("exp->exp2");
  exp2 = new Exp2(scanner, out);
  PROGRESS("exp->op_exp");
  op_exp = new Op_exp(scanner, out);
  DOWN
}

void Exp::typeCheck() {
  UP
  PROGRESS_T("exp")
  exp2->typeCheck();
  op_exp->typeCheck();
  if (op_exp->nTermType == NO_TYPE) 
    nTermType = exp2->nTermType;
  else if (exp2->nTermType != op_exp->nTermType) {
    std::cout << exp2->nTermType << " " << op_exp->nTermType << std::endl;
    nTermType = ERROR_TYPE; }
  else 
    nTermType = exp2->nTermType;  
  DOWN
}

void Exp::makeCode(OutBuffer* out) {;
  PROGRESS_M("Exp");
  if (op_exp->nTermType == NO_TYPE)
    exp2->makeCode(out);
  else if (op_exp->nTermType == OP_GREAT_TYPE) {
    op_exp->makeCode(out);
    exp2->makeCode(out);
    (*out) << "LES\n";	// FIXME: was LESS
  }  else if (op_exp->nTermType == OP_UNEQUAL_TYPE) {
    exp2->makeCode(out);
    op_exp->makeCode(out);
    (*out) << "NOT\n";	// this handles !
  } else {
    exp2->makeCode(out);
    op_exp->makeCode(out);
  }  
}

Exp::~Exp() {
  delete exp2;
  delete op_exp;
}
