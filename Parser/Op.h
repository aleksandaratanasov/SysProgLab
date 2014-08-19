#ifndef _DEF_Op_
#define _DEF_Op_

#include "Nterm.h"

#include "Op.h"

class Scanner;

class Op: public Nterm {
 
 public:
 
  Op(Scanner*, OutBuffer*);
 
  virtual ~Op();
  
  virtual void typeCheck();
  virtual void makeCode(OutBuffer* out);
  
};

#endif