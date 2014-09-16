#include "Parser.h"
#include "Prog.h"
#include "../Scanner/Scanner.h"
#include <iostream>
#include <time.h> // For measuring the compilation time

using std::cout;
using std::endl;
using std::cerr;

Parser::Parser(Scanner* scanner, OutBuffer* out) {
  clock_t start, end;
  int typeErrors, parseErrors;
  
  start = clock();
  
  scanner->nextToken();
  cout << "Starting Parser..." << endl;

  // Start the parsing process
  Prog* prog = new Prog(scanner, out, parseErrors, typeErrors);

  // Check all types
  prog->typeCheck();
  // Generate the interpreter code
  prog->makeCode(out);

  delete prog;

  if (typeErrors == 0 && parseErrors == 0)
    cout << "\n  **  Compilation successful!  **\n" << endl;
  else
    cout << "\n\n------------------------------\n\nCompilation failed! You have following errors:\n\n\tParse errors: " << parseErrors << "\n\tType errors: " << typeErrors << "\n\n------------------------------\n\n" << endl;

  end = clock();
  
  cout << "End Parser" << endl << "Used time: " << (double)(end-start)/CLOCKS_PER_SEC << " seconds" << endl;
}

Parser::~Parser() {
  
}
