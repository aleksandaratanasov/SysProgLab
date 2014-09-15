#ifndef _DEF_Array_
#define _DEF_Array_


#include "Nterm.h"

#include "Array.h"

class Scanner;

class Array: public Nterm {
 
 public:
 
  Array(Scanner*, OutBuffer*);
 
  virtual ~Array();
  
  virtual void typeCheck();
  virtual void makeCode(OutBuffer* out);
  
};

#endif