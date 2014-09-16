#ifndef SCANNER_H_
#define SCANNER_H_

// TODO: no longer needed; used to print a token once it is recognized as such by the scanner
#define TOKEN //cout << "Token: " << lexem << endl;

class Symtable;
class Token;
class ThreadInBuffer;
class Information;
class InBuffer;

template <class type>

class ObjectContainer;

// Generates tokens from a given source file using a finite state machine that implements the language's grammar
class Scanner {

  // All states of the finite state machine
  friend void  scanner_State_Aequi_1(Scanner*);
  friend void  scanner_State_Aequi_2(Scanner*);
  friend void  scanner_State_Ampersand(Scanner*);
  friend void  scanner_State_Comment(Scanner*);
  friend void  scanner_State_Comment_end(Scanner*);
  friend void  scanner_State_Curly_BC(Scanner*);
  friend void  scanner_State_Curly_BO(Scanner*);
  friend void  scanner_State_Division(Scanner*);
  friend void  scanner_State_Equal(Scanner*);
  friend void  scanner_State_ExclamationMark(Scanner*);
  friend void  scanner_State_Greater(Scanner*);
  friend void  scanner_State_Identifier(Scanner*);
  friend void  scanner_State_Integer(Scanner*);
  friend void  scanner_State_Less(Scanner*);
  friend void  scanner_State_Minus(Scanner*);
  friend void  scanner_State_Multi(Scanner*);
  friend void  scanner_State_Not (Scanner*);
  friend void  scanner_State_Plus(Scanner*);
  friend void  scanner_State_Round_BC(Scanner*);
  friend void  scanner_State_Round_BO(Scanner*);
  friend void  scanner_State_Semikolon(Scanner*);
  friend void  scanner_State_Square_BC(Scanner*);
  friend void  scanner_State_Square_BO(Scanner*);
  friend void  scanner_State_Start(Scanner*);
  friend void  scanner_State_Unknown_Letter(Scanner*);  // For handling errors when an unknown character is detected

  char* lexem;
  const char* message;
  int length;
  char* currentChar;
  unsigned int tokenType,line,column;
  long value;

  InBuffer* inBuffer;
  ObjectContainer<Information>* IOC;
  Symtable* symtab;

  void (*state)(Scanner*);

  void getValue();

public:
  Token* token;

  // Creates a finite state machine that stores all the detected tokens in a given source file (by reading it
  // using a buffer) in a symbol table
  Scanner(ObjectContainer<Information>*, InBuffer*, const char** , unsigned int );
  //Scanner(ObjectContainer<Information>* IOC, const char* path, const char* keywords[], unsigned int argv);

  ~Scanner();

  // Checks if a character is a number (0..9); returns true if a number
  static bool isDigit(char* c);

  // Checks if a character is a letter (a..zA..Z); returns true if a letter
  static bool isLetter(char* c);

  // Creates a token
  void nextToken();

  // Same as nextToken() but also checks if the lexeme hasn't already been detected previously in the give source file
  // and marks its type as a duplicate
  void newIdentifier();

};

#endif /* AUTOMAT_H_ */
