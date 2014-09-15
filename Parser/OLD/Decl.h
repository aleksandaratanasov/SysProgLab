#ifndef _DEF_Decl_
#define _DEF_Decl_


#include "Nterm.h"

#include "Decl.h"

class Scanner;
class Array;
class Token;

class Decl: public Nterm {
 
  Array* array;
    
 public:
 
  Decl(Scanner*, OutBuffer*);
 
  virtual ~Decl();
  
  virtual void typeCheck();
  virtual void makeCode(OutBuffer* out);
  
};

#endif