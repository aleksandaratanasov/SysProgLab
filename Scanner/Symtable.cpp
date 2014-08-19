#define SYMTAB_SIZE 128

#include "Symtable.h"
#include "Information.h"
#include "ListElement.h"
#include "../Container/ObjectContainer.h"
#include "t_const.h"

#include <iostream>
#include <cmath>

#include "List.h"

Symtable::Symtable(ObjectContainer<Information>* IOC) {
  maxFill = 50; // initial maximum of entries
  size = SYMTAB_SIZE;
  table = new List[size];
  count = 0;
  steps = 1;
  this->IOC = IOC;
  LEOC = new ObjectContainer<ListElement>(4096);
}

Symtable::~Symtable() {
  delete[] table;
  delete LEOC;
}

unsigned int Symtable::createHashcode(char* lexem) {
  unsigned int hashcode = 0;
  int i = 0;
  while (lexem[i] != '\0') {
    hashcode += exp(2 * log((unsigned int) lexem[i] + 1)) + (unsigned int) lexem[i];
    ++i;
  }
  return hashcode;
}

inline void Symtable::reorganize() {
  steps += 5;
  int newSize = steps * SYMTAB_SIZE + size;
  std::cout << steps << std::endl;
  List* oldTable = table;
  table = new List[newSize];

  ListElement* tmp;
  for (unsigned int i = 0; i < size; ++i) {
    while ((tmp = oldTable[i].removeFirst()) != 0) {
      tmp->next = 0;
      table[tmp->data->getHashCode() % newSize].append(tmp);
    }
  }
  size = newSize;
  delete[] oldTable;
}

Information* Symtable::insert(char* lexem, int length, int ttype) {
	unsigned int hashcode = createHashcode(lexem);
	Information* tmp = table[hashcode % size].searchFor(lexem);
	if (tmp == 0) {
		ListElement* NLE = LEOC->newObject();
		NLE->data = IOC->newObject();
		NLE->data->initialize(lexem, length, ttype, hashcode);
		table[hashcode % size].append(NLE);
		++count;
		//std::cout << "Count:  " << count << " Lexem " << lexem << std::endl;
		if ((double) count / size * 100 > maxFill) 
			reorganize();
		tmp = NLE->data;
	}
	return tmp;
}

void Symtable::insertKeywords(int argv, const char* keywords[]) {
	for (int i = 0; i < argv; ++i) {
		int length = 1;
		while (keywords[i][length] != '\0')
			++length;
		insert((char*) keywords[i], length, TTYPE_KEYWORD);
	}
}

Information* Symtable::searchFor(char* lexem) {
	return table[createHashcode(lexem) % size].searchFor(lexem);
}
/*
void Symtable::print() {
	std::cout << "-------------------------------------" << std::endl;
	for (unsigned int i = 0; i < size; ++i) {
		std::cout << "Zelle " << i << "\n";
		table[i].print();
	}
}
*/
