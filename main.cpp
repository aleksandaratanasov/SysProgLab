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
  Parser* parser = new Parser(scanner, out);

  // clean everything
  delete inBuf;
  delete out;
  delete scanner;
  delete IOC;
  delete parser;

  return 0;
}
