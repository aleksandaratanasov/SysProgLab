#include "Scanner.h"

#define LEXEM_LENGTH 512

#include "Symtable.h"
#include "../Container/ObjectContainer.h"
#include "Token.h"
#include "Information.h"
#include "t_const.h"

#include "../IO/ThreadInBuffer.h"
#include "../IO/OutBuffer.h"
#include "../IO/ThreadFileOutBuffer.h"
#include "../IO/ConsoleOutBuffer.h"

#include <iostream>
#include <cstdlib>
#include <limits.h>

using std::cout;
using std::endl;
using std::cerr;

void scanner_State_Start(Scanner*);
void scanner_State_Aequi_1(Scanner*);
void scanner_State_Aequi_2(Scanner*);
void scanner_State_Comment_end(Scanner*);

Scanner::Scanner(ObjectContainer<Information>* IOC, InBuffer* inBuffer, const char* keywords[], unsigned int argv) {

  this->inBuffer = inBuffer;
  this->IOC = IOC;
  symtab = new Symtable(IOC);

  symtab->insertKeywords(argv, keywords);

  state = scanner_State_Start;
  lexem = new char[LEXEM_LENGTH];
  currentChar = inBuffer->getChar();
  lexem[0] = *currentChar;
  token = new Token();
}

Scanner::~Scanner() {
  delete symtab;
  delete lexem;
  delete token;
}

void Scanner::newIdentifier() {
  do {
    state(this);
    lexem[length++] = *currentChar;
    if (tokenType == 0)
      currentChar = inBuffer->getChar();
  } while (tokenType == 0);

  lexem[--length] = '\0';

  if (tokenType == TTYPE_IDENTIFIER) {
    if (symtab->searchFor(lexem) != 0)
      tokenType = TTYPE_EXISTING_IDENTIFIER;
    else
      tokenType = TTYPE_CONFIRMED_IDENTIFIER;
  }

  TOKEN

  Information*  info = symtab->insert(lexem, length, tokenType);
  token->makeToken(info, line, column, value);
}


void Scanner::nextToken() {
  do {
    state(this);
    lexem[length++] = *currentChar;
    if (tokenType == 0)
      currentChar = inBuffer->getChar();
  } while (tokenType == 0);

  lexem[--length] = '\0';

  TOKEN

  Information* info = symtab->insert(lexem, length, tokenType);
  token->makeToken(info, line, column, value);
}

void Scanner::getValue() {
  lexem[length] = '\0';
  value = atol(lexem);
  if (value == LONG_MAX || value == LONG_MIN) {
    tokenType = TTYPE_LONG_RANGE_ERROR;
  }
}

bool Scanner::isDigit(char* c) {
  if ((*c >= '0' && *c <= '9'))
    return true;
  return false;
}

bool Scanner::isLetter(char* c) {
  if ((*c >= 'a' && *c <= 'z') || (*c >= 'A' && *c <= 'Z'))
    return true;
  return false;
}

// States of the finite state machine
void scanner_State_Identifier(Scanner* scanner){
  if (!Scanner::isDigit(scanner->currentChar) && !Scanner::isLetter(scanner->currentChar)) {
    scanner->tokenType = TTYPE_IDENTIFIER;
    scanner->state = scanner_State_Start;
  }
}

void scanner_State_Integer(Scanner* scanner){
  if (!Scanner::isDigit(scanner->currentChar)) {
    scanner->tokenType = TTYPE_INT;
    scanner->getValue();
    scanner->state = scanner_State_Start;
  }
}

void scanner_State_Less(Scanner* scanner){
  if (*scanner->currentChar == '=') { // Check if this is not the beginning of the sign <=>
    scanner->state = scanner_State_Aequi_1;
  } else {
    scanner->tokenType = TTYPE_LESS;
    scanner->state = scanner_State_Start;
  }
}

void scanner_State_Aequi_1(Scanner* scanner){
  if (*scanner->currentChar == '>') { // For finilizing a <=> if such sign is detected
    scanner->state = scanner_State_Aequi_2;
  } else {
    scanner->tokenType = TTYPE_LESS;
    scanner->length--;
    scanner->inBuffer->back(2);
    scanner->state = scanner_State_Start;
  }
}

void scanner_State_Aequi_2(Scanner* scanner){
  scanner->tokenType = TTYPE_AEQUI;
  scanner->state = scanner_State_Start;
}

void scanner_State_Comment(Scanner* scanner){
  if (*scanner->currentChar == '*') // For finilizing a (* if such sign is detected
    scanner->state = scanner_State_Comment_end;
}

void scanner_State_Comment_end(Scanner* scanner){
  if (*scanner->currentChar == ')') { // For finilizing a *) if such sign is detected
    scanner->state = scanner_State_Start;
    scanner->length = 0;
  } else
    scanner->state = scanner_State_Comment;
}

void scanner_State_Round_BO(Scanner* scanner){
  if (*scanner->currentChar == '*') { // For detecting a (*
    scanner->state = scanner_State_Comment;
  } else {
    scanner->tokenType = TTYPE_R_B_O;
    scanner->state = scanner_State_Start;
  }
}

void scanner_State_Round_BC(Scanner* scanner){
  scanner->tokenType = TTYPE_R_B_C;
  scanner->state = scanner_State_Start;
}

void scanner_State_Ampersand(Scanner* scanner){
  scanner->tokenType = TTYPE_AMP;
  scanner->state = scanner_State_Start;
}

void scanner_State_Curly_BC(Scanner* scanner){
  scanner->tokenType = TTYPE_C_B_C;
  scanner->state = scanner_State_Start;
}

void scanner_State_Curly_BO(Scanner* scanner){
  scanner->tokenType = TTYPE_C_B_O;
  scanner->state = scanner_State_Start;
}

void scanner_State_Division(Scanner* scanner){
  scanner->tokenType = TTYPE_DIV;
  scanner->state = scanner_State_Start;
}

void scanner_State_Equal(Scanner* scanner){
  scanner->tokenType = TTYPE_EQUALS;
  scanner->state = scanner_State_Start;
}

void scanner_State_Greater(Scanner* scanner){
  scanner->tokenType = TTYPE_GREATER;
  scanner->state = scanner_State_Start;
}

void scanner_State_Minus(Scanner* scanner){
  scanner->tokenType = TTYPE_MINUS;
  scanner->state = scanner_State_Start;
}

void scanner_State_Multi(Scanner* scanner){
  scanner->tokenType = TTYPE_MULT;
  scanner->state = scanner_State_Start;
}

void scanner_State_Not(Scanner* scanner){
  scanner->tokenType = TTYPE_NOT;
  scanner->state = scanner_State_Start;
}

void scanner_State_Plus(Scanner* scanner){
  scanner->tokenType = TTYPE_PLUS;
  scanner->state = scanner_State_Start;
}

void scanner_State_Semikolon(Scanner* scanner){
  scanner->tokenType = TTYPE_SEMI;
  scanner->state = scanner_State_Start;

}

void scanner_State_Square_BC(Scanner* scanner){
  scanner->tokenType = TTYPE_S_B_C;
  scanner->state = scanner_State_Start;
}

void scanner_State_Square_BO(Scanner* scanner){
  scanner->tokenType = TTYPE_S_B_O;
  scanner->state = scanner_State_Start;
}

void scanner_State_Unknown_Letter(Scanner* scanner){
  scanner->tokenType = TTYPE_UNKNOWN_LETTER;
  scanner->state = scanner_State_Start;
}

// Start of the FSM; every time a token is detected the FSM returns to this initial state
void scanner_State_Start(Scanner* scanner){

  scanner->line   = scanner->inBuffer->getLine();
  scanner->column = scanner->inBuffer->getColumn();
  scanner->length = 0;
  scanner->tokenType = 0;

  if (Scanner::isDigit(scanner->currentChar)) {
    scanner->state = scanner_State_Integer;
    return;
  }

  if (Scanner::isLetter(scanner->currentChar)) {
    scanner->state = scanner_State_Identifier;
    return;
  }

  switch (*(scanner->currentChar)) {
    case '=':
      scanner->state = scanner_State_Equal;
      break;
    case '<':
      scanner->state = scanner_State_Less;
      break;
    case '>':
      scanner->state = scanner_State_Greater;
      break;
    case '&':
      scanner->state = scanner_State_Ampersand;
      break;
    case '*':
      scanner->state = scanner_State_Multi;
      break;
    case '+':
      scanner->state = scanner_State_Plus;
      break;
    case '-':
      scanner->state = scanner_State_Minus;
      break;
    case '/':
      scanner->state = scanner_State_Division;
      break;
    case '!':
      scanner->state = scanner_State_Not;
      break;
    case '(':
      scanner->state = scanner_State_Round_BO;
      break;
    case ')':
      scanner->state = scanner_State_Round_BC;
      break;
    case '[':
      scanner->state = scanner_State_Square_BO;
      break;
    case ']':
      scanner->state = scanner_State_Square_BC;
      break;
    case '{':
      scanner->state = scanner_State_Curly_BO;
      break;
    case '}':
      scanner->state = scanner_State_Curly_BC;
      break;
    case ';':
      scanner->state = scanner_State_Semikolon;
      break;
    case '\0':
      scanner->tokenType = TTYPE_FILE_END;
      break;
    // Blanks (space, new line and tabulation) are ignored
    case ' ':
    case '\n':
    case '\t':
      break;
    default:
      scanner->state = scanner_State_Unknown_Letter;  // Error upon detecting an unknown character
      break;
  }

}
