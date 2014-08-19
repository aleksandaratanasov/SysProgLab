#include <iostream>

#include "Token.h"
#include "Information.h"

Token::Token(Information* info, int line, int column, long value) {
	this->info = info;
	this->line = line;
	this->column = column;
	this->value = value;
}

void Token::makeToken(Information* info, int line, int column, long value) {
	this->info = info;
	this->line = line;
	this->column = column;
	this->value = value;
}

Token::~Token() {
}

Token::Token() {
}

long Token::getValue() {
	return value;
}

int Token::getLine() {
	return line;
}

int Token::getColumn() {
	return column;
}

Information* Token::getInformation() {
	return info;
}

Token* Token::clone() {
  return new Token(info, line, column, value);
}