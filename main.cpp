#include "Scanner/Scanner.h"
#include "Scanner/Information.h"
#include "Scanner/Token.h"
#include <iostream>
#include "Scanner/t_const.h"
#include "Parser/Parser.h"

#include "Container/ObjectContainer.h"

#include "IO/ConsoleOutBuffer.h"
#include "IO/ThreadFileOutBuffer.h"
#include "IO/ThreadInBuffer.h"
#include "IO/InBuffer.h"

//TEST
#include "Parser/ListT.h"
#include "Parser/PARSER_NEW.h"

using std::cout;
using std::endl;

int main(int argc, char **argv) {
  if (argc < 3) {
    cout << "Usage: hskac <in:source-file> <out:interpreter-file>" << endl;
    return 1;
  } else {
    cout << "Running hskac..." << endl << "\n  Input File : " << argv[1] <<  endl << "  Output File: " << argv[2]  <<  endl <<  endl;
  }

  // create the set of keywords
  const char* keywords[] = {"print","read","int","while","if","else"};

  ObjectContainer<Information>* IOC = new ObjectContainer<Information>(512);

  InBuffer* inBuf = new ThreadInBuffer(argv[1]);
//  InBuffer* inBuf = new ThreadInBuffer("in.txt");
  OutBuffer* out = new ThreadFileOutBuffer(argv[2]);
//  OutBuffer* out = new ThreadFileOutBuffer("out.txt");

  Scanner* scanner = new Scanner(IOC, inBuf, keywords, 6);
//  Parser* parser = new Parser(scanner, out);

  // TEST START
//  int pE, tE;
//  ListT<Node>* testList = new ListT<Node>();
//  ProgNEW* pr1 = new ProgNEW(scanner, out, tE, pE);
//  DeclsNEW* pr2 = new DeclsNEW(scanner, out, tE, pE);
//  DeclNEW* pr3 = new DeclNEW(scanner, out, tE, pE);
//  StatementsNEW* pr4 = new StatementsNEW(scanner, out, tE, pE);
//  testList->append(pr1);
//  testList->append(pr2);
//  testList->append(pr3);
//  testList->append(pr4);
//  testList->print();
//  delete testList;
//  return 1;
  // TEST END

  ParserNEW *parser = new ParserNEW(scanner, out);

  // clean everything
  delete inBuf;
  delete out;
  delete scanner;
  delete IOC;
  delete parser;

  return 0;
}
