#ifndef _DEF_Statements_
#define _DEF_Statements_

#include "Nterm.h"

#include "Statements.h"

class Scanner;
class Statements;
class Statement;

class Statements: public Nterm {

  Statement* statement;
  Statements* statements;
  
 public:
 
  Statements(Scanner*, OutBuffer*);
 
  virtual ~Statements();

  virtual void typeCheck();
  virtual void makeCode(OutBuffer* out);
  
};

#endif