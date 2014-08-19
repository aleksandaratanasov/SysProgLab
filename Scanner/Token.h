#ifndef __TOKEN__DEFINED__
#define __TOKEN__DEFINED__

class Information;

// A data container that stores information about a token
class Token {

  int line;
  int column;

  // If a token is a number, we store its value
  long value;

  Information* info;

public:

  // Creates a new token given the information about the lexem it stores,
  // value (if a number) and position of the lexem's first character in
  // a given source code
  Token(Information* info, int line, int column, long value);

  Token();

  ~Token();

  // If token is a number, returns its value
  long getValue();

  void makeToken(Information* info, int line, int column, long value);

  // Returns the line of the token in a given source file based on the first character of the lexem it stores
  int getLine();
  // Returns the column of the token in a given source file based on the first character of the lexem it stores
  int getColumn();
  // Returns the information about the lexem the token stores
  Information* getInformation();

  // TODO: no longer needed; prints a token in the console
  void print();

  // Clones a token
  Token* clone();
};

#endif
