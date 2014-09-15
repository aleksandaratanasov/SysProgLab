#ifndef _DEF_Decls_
#define _DEF_Decls_


#include "Nterm.h"

#include "Decls.h"

class Scanner;
class Decl;

class Decls: public Nterm {
  
  Decl* decl; 
  Decls* decls; 
 
 public:
 
  Decls(Scanner*, OutBuffer*);
 
  virtual ~Decls();
  
  virtual void typeCheck();
  virtual void makeCode(OutBuffer* out);
  
};

#endif