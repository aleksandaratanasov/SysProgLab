#include "Prog.h"
#include "Decls.h"
#include "Statements.h"
#include "../Scanner/Scanner.h"
#include "../IO/OutBuffer.h"

Prog::Prog(Scanner* scanner, OutBuffer* out, int& pE, int &tE):Nterm(scanner) {
  UP
//  PROGRESS("prog->Decls")
  decls = new Decls(scanner, out);
  delete decls;
  PROGRESS("prog->Statements")
  statements = new Statements(scanner, out);
  delete statements;
  pE = parseErrors;
  tE = typeErrors;
  OUT("back at Prog")
  DOWN
}

void Prog::typeCheck() {
  UP
  PROGRESS_T("prog")
  nTermType = NO_TYPE;
}

void Prog::makeCode(OutBuffer* out) {
  PROGRESS_M("prog");
  (*out) << "STP\n";  
}

Prog::~Prog() {
}
