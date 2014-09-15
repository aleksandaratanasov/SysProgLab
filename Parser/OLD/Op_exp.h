#ifndef _DEF_Op_exp_
#define _DEF_Op_exp_

#include "Nterm.h"

#include "Op_exp.h"

class Scanner;
class Op;
class Exp;

class Op_exp: public Nterm {
 
  Op* op;
  Exp* exp;
  
 public:
 
  Op_exp(Scanner*, OutBuffer*);
 
  virtual ~Op_exp();
  
  virtual void typeCheck();
  virtual void makeCode(OutBuffer* out);
  
};

#endif