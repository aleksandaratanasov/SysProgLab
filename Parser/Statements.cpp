#include "Statement.h"
#include "Statements.h"

#include "../Scanner/t_const.h"
#include "Nterm.h"

Statements::Statements(Scanner* scanner, OutBuffer* out):Nterm(scanner) {
  UP
  while (scanner->token->getInformation()->getType() != TTYPE_FILE_END && !scanner->token->getInformation()->equals("}") &&  nTermType != ERROR_TYPE) {
    PROGRESS("statements->statement");
    statement = new Statement(scanner, out);
    if (scanner->token->getInformation()->getType() == TTYPE_SEMI) {
      PROGRESS("statement->statements");
      scanner->nextToken();
      cloneTokenData();
      statement->typeCheck();
      statement->makeCode(out);
      delete statement;
    } else
    	parseError("Missing ';'");
  }
  DOWN
}

void Statements::typeCheck() {
  UP
  PROGRESS_T("statements")
  nTermType = NO_TYPE;
  DOWN
}

void Statements::makeCode(OutBuffer* out) {
  PROGRESS_M("Statements");
  (*out) << "NOP\n"; // FIXME: this is only the case when € is encountered. Block code inside conditional sturctures (while/if:else)
                     // should run generate code after their conditional jumps are written to the interpreter file
}

Statements::~Statements() {
}
