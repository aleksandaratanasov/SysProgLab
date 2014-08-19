#ifndef _NTERM_
#define _NTERM_

#define PROGRESS(a) 	std::cout << entry; for (unsigned int i = 0; i < entry; ++i) std::cout << ".  "; std::cout << "Parser: " << a << " via " << info->getLexem() << " at " << line << "/" << column << std::endl;
#define PROGRESS_T(a) 	for (unsigned int i = 0; i < entry; ++i) std::cout << ".  "; std::cout << "typeCheck: " << a << " / " << info->getLexem() << " at " << line << "/" << column << std::endl;
#define PROGRESS_M(a) 	std::cout << "MakeCode: " << a << " / " << info->getLexem() << " at " << line << "/" << column << std::endl;
#define OUT(a)        //std::cout << a << std::endl;
#define DOWN            --entry;
#define UP              ++entry;

#include <iostream>

#include "../Scanner/Token.h"
#include "../Scanner/Scanner.h"
#include "../Scanner/Information.h"
#include "../Scanner/t_const.h"
#include "../IO/OutBuffer.h"

#define ERROR_TYPE 			999
#define EOF 				2
#define NO_TYPE 			3
#define ARRAY_TYPE			4
#define INT_TYPE			5
#define OP_PLUS_TYPE		103
#define OP_MINUS_TYPE		104
#define OP_MULT_TYPE		106
#define OP_DIV_TYPE			105
#define OP_LESS_TYPE		108
#define OP_GREAT_TYPE		107
#define OP_EQUAL_TYPE		109
#define OP_UNEQUAL_TYPE		120
#define OP_AND_TYPE			112

class Scanner;
class Information;
class OutBuffer;

class Nterm {
 
 protected:
   
  static unsigned int entry;
  static unsigned int parseErrors;
  static unsigned int typeErrors;
 
  Scanner* scanner; 
  unsigned int line,column;
  long value;
  Information* info;	
 
  void parseError(const char* message);
  void typeError(const char* message);

  void cloneTokenData();
  
  static int marke;
  
 public:
 
  unsigned int nTermType;
   
  Nterm(Scanner* scanner);
  virtual ~Nterm();
  
  virtual void typeCheck() = 0;
  virtual void makeCode(OutBuffer*) = 0;
    
};

#endif
