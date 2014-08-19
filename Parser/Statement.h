#ifndef _DEF_Statement_
#define _DEF_Statement_

#include "Nterm.h"

#include "Statement.h"

class Scanner;
class Index;
class Exp;
class Statements;
class Information;
class Token;

class Statement: public Nterm {
  
  Index* index;
  Exp* exp;
  Statements* statements;
  Statement* statement1;
  Statement* statement2;
    
  int type;
  
 public:
 
  Statement(Scanner*, OutBuffer*);
 
  virtual ~Statement();
  
  virtual void typeCheck();
  virtual void makeCode(OutBuffer* out);
  
};

#endif