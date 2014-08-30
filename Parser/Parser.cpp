#include "Parser.h"
#include "Prog.h"
#include "../Scanner/Scanner.h"
#include <iostream>
#include <time.h> // For measuring the compilation time

Parser::Parser(Scanner* scanner, OutBuffer* out) {
  clock_t start, end;
  int typeErrors, parseErrors;
  
  start = clock();
  
  scanner->nextToken();
  std::cout << "Starting Parser..." << std::endl;

  // Start the parsing process
  Prog* prog = new Prog(scanner, out, parseErrors, typeErrors);

  // Check all types
  prog->typeCheck();
  // Generate the interpreter code
  prog->makeCode(out);

  delete prog;

  if (typeErrors == 0 && parseErrors == 0)
    std::cout << "\n  **  Compilation successful!  **\n" << std::endl;
  else
    std::cout << "\n\n------------------------------\n\nCompilation failed! You have following errors:\n\n\tParse errors: " << parseErrors << "\n\tType errors: " << typeErrors << "\n\n------------------------------\n\n" << std::endl;

  end = clock();
  
  std::cout << "End Parser" << std::endl << "Used time: " << (double)(end-start)/CLOCKS_PER_SEC << " seconds" << std::endl;
}

Parser::~Parser() {
  
}
