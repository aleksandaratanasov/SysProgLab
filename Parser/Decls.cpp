#include "Decl.h"
#include "Decls.h"
#include "Statements.h"

#include "Nterm.h"
#include "../Scanner/t_const.h"

Decls::Decls(Scanner* scanner, OutBuffer* out):Nterm(scanner) {
  UP
  while (scanner->token->getInformation()->equals("int")) {
    PROGRESS("Decls->Decl")
    scanner->newIdentifier();
    decl = new Decl(scanner, out);
    if (scanner->token->getInformation()->getType() == TTYPE_SEMI) {
      PROGRESS("Decls->Decl")
      scanner->nextToken();
      cloneTokenData();
      decl->typeCheck();
      decl->makeCode(out);
      delete decl;
    } else
      parseError("Missing Semikolon");
  }
  DOWN
}

void Decls::typeCheck() {
  UP
  PROGRESS_T("decls")
  nTermType = NO_TYPE;
  PROGRESS_T("decls ende")
  DOWN
}

void Decls::makeCode(OutBuffer* out) {
  PROGRESS_M("Decls");
}

Decls::~Decls() {
}
