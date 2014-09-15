#ifndef _DEF_Exp_
#define _DEF_Exp_

#include "Nterm.h"

#include "Exp.h"


class Scanner;
class Exp2;
class Op_exp;

class Exp: public Nterm {
 
  Exp2* exp2;
  Op_exp* op_exp;
  
 public:
 
  Exp(Scanner*, OutBuffer*);
 
  virtual ~Exp();
  
  virtual void typeCheck();
  virtual void makeCode(OutBuffer* out);
  
};

#endif