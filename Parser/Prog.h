#ifndef _DEF_Prog_
#define _DEF_Prog_


#include "../Scanner/Information.h"
#include "../Scanner/Scanner.h"
#include "Nterm.h"

#include "Prog.h"

class Scanner;
class Decls;
class Statements;

class Prog: public Nterm {
 
  Decls* decls;
  Statements* statements;
  
 public:
 
  Prog(Scanner*, OutBuffer*, int&, int&);
 
  virtual ~Prog();
  
  virtual void typeCheck();
  virtual void makeCode(OutBuffer* out);
  
};

#endif