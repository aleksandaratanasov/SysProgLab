#ifndef _DEF_Exp2_
#define _DEF_Exp2_

#include "Nterm.h"

#include "Exp2.h"

class Scanner;
class Index;
class Exp;
class Exp2;
class Token;

class Exp2: public Nterm {
  
  Exp* exp;
  Exp2* exp2;
  Index* index;
    
  int type;
 
 public:
 
  Exp2(Scanner*, OutBuffer*);
 
  virtual ~Exp2();
  
  virtual void typeCheck();
  virtual void makeCode(OutBuffer* out);
  
};

#endif