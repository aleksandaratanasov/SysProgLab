#include "Op.h"

Op::Op(Scanner* scanner, OutBuffer* out):Nterm(scanner) {
  UP
  info = scanner->token->getInformation();
  scanner->nextToken();
  DOWN
}

void Op::typeCheck() {
  UP
  PROGRESS_T("op");
  nTermType = info->getType();
  DOWN
}

void Op::makeCode(OutBuffer* out) {
  PROGRESS_M("OP");
  switch (info->getType()) {
    case TTYPE_PLUS:
      (*out) << "ADD\n";
      break;
    case TTYPE_MINUS:
      (*out) << "SUB\n";
      break;
    case TTYPE_MULT:
      (*out) << "MUL\n";
      break;
    case TTYPE_DIV:
      (*out) << "DIV\n";
      break;
    case TTYPE_GREATER:
      (*out) << "LES\nNOT\n"; // FIX: partial fix for greater operator; this is not how it's described in the PDF documentation
      break;
    case TTYPE_LESS:
      (*out) << "LES\n";
      break;
    case TTYPE_EQUALS:
      (*out) << "EQU\n";
      break;
    case TTYPE_N_EQUALS:	// FIXME: this should be in EXP2 and Exp since the "!" is handled there (OR NOT?! Think about it)
      (*out) << "NOT\n";
      break;
    case TTYPE_AEQUI:
      (*out) << "EQU\nNOT\n"; //FIX: added "NOT\n"; REASON: combined with NOT - FIXME: when debugging <=> we come here without the NOT so it is evaluated as =
      break;
    case TTYPE_AMP:
      (*out) << "AND\n";
      break;
  }

}

Op::~Op() {
}
