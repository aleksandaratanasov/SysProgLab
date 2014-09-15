#ifndef _PARSER_
#define _PARSER_

//#include "../Scanner/Scanner.h"
//#include "../scanner/token.h"

class Scanner;
class OutBuffer;

// The parser verifies if the parsed tokens are part of a meaningful source code
// (meaningful = obeys the rules of the language's grammar), checks their types
// and finally generates code that is written to an interpreter file, which then
// can be run by an interpreter
// The parsing process is based on a top down parsing tree, where we start from
// from the highest node (Prog) and try to go as deep as possible following a type
// verification
class Parser {

public:
  // Creates a parser given a scanner and buffer for writing an interpreter file
  Parser(Scanner*, OutBuffer*);

  ~Parser();
    
};

#endif
