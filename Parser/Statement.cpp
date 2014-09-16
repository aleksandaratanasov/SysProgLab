#include "Statement.h"
#include "Statements.h"
#include "Index.h"
#include "Exp.h"
#include "../Scanner/Scanner.h"

#include "../Scanner/Token.h"
#include "../Scanner/t_const.h"
#include "../Scanner/Information.h"
#include "../Scanner/Scanner.h"
#include "../IO/OutBuffer.h"

using std::cout;
using std::endl;
using std::cerr;

Statement::Statement(Scanner* scanner, OutBuffer* out):Nterm(scanner) {
  UP
  type = 0;
  exp = 0;
  index = 0;
  statement1 = 0;
  statement2 = 0;
  statements = 0;
  if (scanner->token->getInformation()->getType() == TTYPE_CONFIRMED_IDENTIFIER || scanner->token->getInformation()->getType() == TTYPE_ARRAY) {
    PROGRESS("statement->index");
    scanner->nextToken();
    index = new Index(scanner, out);
    if (scanner->token->getInformation()->getType() == TTYPE_EQUALS) {
      PROGRESS("statement->exp");
      scanner->nextToken();
      exp = new Exp(scanner, out);
      type = 1;
    } else {
      parseError("Missing '='");
    }
  }
  else if (scanner->token->getInformation()->equals("print")) {
    scanner->nextToken();
    if (scanner->token->getInformation()->getType() == TTYPE_R_B_O) {
      PROGRESS("statement->exp");
      scanner->nextToken();
      exp = new Exp(scanner, out);
      if (scanner->token->getInformation()->getType() == TTYPE_R_B_C) {
	type = 2;
	scanner->nextToken();
      } else
	parseError("Missing closing ')'");
    } else {
      parseError("Missing '('");
    }
  }
  else if (scanner->token->getInformation()->equals("read")) {
    scanner->nextToken();
    if (scanner->token->getInformation()->getType() == TTYPE_R_B_O) {
      scanner->nextToken();
      if (scanner->token->getInformation()->getType() == TTYPE_CONFIRMED_IDENTIFIER) {
	info = scanner->token->getInformation();
	PROGRESS("statement->index");
	scanner->nextToken();
	index = new Index(scanner, out);
	if (scanner->token->getInformation()->getType() == TTYPE_R_B_C) {
	  type = 3;
	  scanner->nextToken();
	} else
	  parseError("Missing closing ')'");
      } else
	parseError("Identifier expected");
    } else {
      parseError("Missing '('");
    }
  }
  else if (scanner->token->getInformation()->getType() == TTYPE_C_B_O) { // FIXME: Somewhere here is the culprit
    PROGRESS("statement->statements");
    scanner->nextToken();
    //cout << " ============================================================================= nextToken() = \"" << scanner->token->getInformation()->getLexem() << "\"" << endl;
    statements = new Statements(scanner, out);
    //cout << " ============================================================================= nextToken():AFTER STATEMENTS = \"" << scanner->token->getInformation()->getLexem() << "\"" << endl;
    if (scanner->token->getInformation()->getType() == TTYPE_C_B_C) {
      scanner->nextToken();
      type = 4;
    } else
      parseError("Missing closing '}'");
  }
  else if (scanner->token->getInformation()->equals("if")) {
    scanner->nextToken();
    if (scanner->token->getInformation()->getType() == TTYPE_R_B_O) {
      PROGRESS("statement->exp");
      scanner->nextToken();
      exp = new Exp(scanner, out);
      if (scanner->token->getInformation()->getType() == TTYPE_R_B_C) {
    	  PROGRESS("statement->statement1");
    	  scanner->nextToken();
    	  statement1 = new Statement(scanner, out);
		  if (scanner->token->getInformation()->equals("else")) {
			  PROGRESS("statement->statement2");
			  scanner->nextToken();
			  statement2 = new Statement(scanner, out);
			  type = 5;
		  } else
			  parseError("'else' expected");
      } else
    	  parseError("Missing ')'");
    } else
      parseError("Missing '('");
  }
  else if (scanner->token->getInformation()->equals("while")) {
    scanner->nextToken();
    if (scanner->token->getInformation()->getType() == TTYPE_R_B_O) {
      PROGRESS("statement->exp");
      scanner->nextToken();
      exp = new Exp(scanner, out);
      if (scanner->token->getInformation()->getType() == TTYPE_R_B_C) {
    	  PROGRESS("statement->statement1");
    	  scanner->nextToken();
    	  statement1 = new Statement(scanner, out);
    	  type = 6;
      } else
    	  parseError("Missing ')'");
    } else
    	parseError("Missing '('");
  }
  else {
    parseError("Expected 'print', 'read', 'if', 'while', '{' or an identifier.");
  }
  DOWN
}

void Statement::typeCheck() {
  UP
  PROGRESS_T("statement")
  nTermType = ERROR_TYPE;	  
  switch (type) {
    case 1: // identifier INDEX = EXP
      exp->typeCheck();
      index->typeCheck();
      if ((exp->nTermType == INT_TYPE || exp->nTermType == ARRAY_TYPE)  && 
         ((info->getType() == TTYPE_CONFIRMED_IDENTIFIER && index->nTermType == NO_TYPE) || (info->getType() == TTYPE_ARRAY && index->nTermType == ARRAY_TYPE)))
        nTermType = NO_TYPE;
      else {
        typeError("incompatible types. ");
        cout << exp->nTermType << " " << info->getType() << " " << index->nTermType << endl;
      }
      break;
    case 2: // print (EXP)
      exp->typeCheck();
      nTermType = NO_TYPE;
      break;
    case 3: // read (identifier INDEX)
      index->typeCheck();
      if ((info->getType() == TTYPE_CONFIRMED_IDENTIFIER && index->nTermType == NO_TYPE) || (info->getType() == TTYPE_ARRAY && index->nTermType == ARRAY_TYPE))
	nTermType = NO_TYPE;
      else
	typeError("incompatible types");
      break;
    case 4: // {STATEMENTS}
      statements->typeCheck();
      nTermType = NO_TYPE;
      break;
    case 5: // if...
      exp->typeCheck();
      statement1->typeCheck();
      statement2->typeCheck();
      if (exp->nTermType == ERROR_TYPE)
        nTermType = ERROR_TYPE;
      else
        nTermType = NO_TYPE;
      break;
    case 6: //while...
      exp->typeCheck();
      statement1->typeCheck();
      if (exp->nTermType == ERROR_TYPE)
        nTermType = ERROR_TYPE;
      else
        nTermType = NO_TYPE;
      break;
    default:
      nTermType = ERROR_TYPE;	  
      typeError("Identifier not defined"); 
      break;
  }
  DOWN
}

void Statement::makeCode(OutBuffer* out) {
  PROGRESS_M("Statement");
  int M1;
  int M2;
  
  switch (type) {
    case 1: //identifier
      exp->makeCode(out);
      (*out) << "LA $" << info->getLexem() << "\n";
      index->makeCode(out);
      (*out) << "STR\n";
      break;
    case 2: //print
      exp->makeCode(out);
      (*out) << "PRI\n";
      break;
    case 3: //read
      (*out) << "REA\n" << "LA $" << info->getLexem() << "\n";
      index->makeCode(out);
      (*out) << "STR\n";
      break;
    case 4: //{...}
      statements->makeCode(out);
      /*
        Problem with infinite while loop occurs when {} are used
        due to a shift in the conditional statement after the block
        it protects. Also applies to the if statement.
        From the generated code it can be seen that the mark for
        the conditional jump is placed after the statements inside
        the {} block and before the loop's condition:

        ---- Statements inside the while loop ----
        #M1 NOP
        LA $a
        LV
        LA $b
        LV
        EQU
        NOT
        JIN #M2
        NOP
        JMP #M1
        #M2 NOP

        This leads to the problem that new values generated inside
        the loop are not pushed on the stack and all that the resulting
        code does is evaluate the loop's condition with the old values
        and then jump back to evaluating the loop's condition. That's why
        ONLY upon entry in the loop's main body variable values are changed
      */
      break;
    case 5: // if ...
      M1 = mark++;
      M2 = mark++;
      exp->makeCode(out);
      (*out) << "JIN #M" << M1 << "\n";
      statement1->makeCode(out);
      (*out) << "JMP #M" << M2
    		 << "\n#M" << M1 << " NOP\n";
      statement2->makeCode(out);
      (*out) << "#M" << M2 << " NOP\n";
      break;
    case 6: // while // FIXME: See case 4
      M1 = mark++;
      M2 = mark++;
      (*out) << "#M" << M1 << " NOP\n";
      exp->makeCode(out);
      (*out) << "JIN #M" << M2 << "\n";
      statement1->makeCode(out);
      (*out) << "JMP #M" << M1 << "\n#M" << M2 << " NOP\n";
      break;
  }
}

Statement::~Statement() {
  if (exp != 0)
    delete exp;
  if (index != 0);
    delete index;
  if (statements != 0)
    delete statements;
  if (statement1 != 0)
    delete statement1;
  if (statement2 != 0)
    delete statement2;
}
