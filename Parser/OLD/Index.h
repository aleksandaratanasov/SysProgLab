#ifndef _DEF_Index_
#define _DEF_Index_


#include "Nterm.h"

#include "Index.h"

class Scanner;
class Exp;

class Index: public Nterm {
 
  Exp* exp;
  
 public:
 
  Index(Scanner*, OutBuffer*);
 
  virtual ~Index();
  
  virtual void typeCheck();
  virtual void makeCode(OutBuffer* out);
  
};

#endif