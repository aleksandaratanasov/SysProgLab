#include "Information.h"
#include "t_const.h"
#include <math.h>
#include <iostream>

Information::Information() {
  lexem = 0;
}

Information::Information(char* lexem, int length, int ttype, unsigned int hashcode) {
  initialize(lexem, length, ttype, hashcode);
}

void Information::initialize(char* lexem, int length, int ttype, unsigned int hashcode) {
  this->lexem = new char[length+1];
  for (; length >= 0; --length) // Copy lexeme
    this->lexem[length] = lexem[length];
  this->ttype = ttype;
  this->hashcode = hashcode;
}

Information::~Information() {
  if (lexem != 0)
    delete lexem;
}

unsigned int Information::getHashCode() {
  return hashcode;
}

char* Information::getLexem() {
  return lexem;
}

bool Information::equals(char* lexem) {
  if (lexem == 0) // fast check for passed empty lexeme
    return false;
  // Use copies of the pointers to the lexem for the comparision
  char* x = lexem;
  char* y = this->lexem;
  while (*x != '\0' && *x == *y) {
    ++x;
    ++y;
  }
  return (*x == *y);
}

/** Gibt den Typ der Information zurück*/

int Information::getType() {
  return this->ttype;
}

void Information::toArray() {
  if (ttype == TTYPE_CONFIRMED_IDENTIFIER)
    ttype = TTYPE_ARRAY;
}
