/*
 * List.cpp
 *
 *  Created on: 19.10.2011
 *      Author: seb
 */

#include "List.h"

#include "ListElement.h"
#include "Information.h"
#include "../Container/ObjectContainer.h"

#include <iostream>

List::List() {
	first = 0;
	last = 0;
	size = 0;
}

List::~List() {
}


void List::append(ListElement* LE) {
	if (first == 0)
		first = LE;
	else
		last->next = LE;
	last = LE;
	++size;
}

ListElement* List::removeFirst() {
	if (first != 0) {
		ListElement* Element = first;
		first = first->next;
		if (first == 0) {
			last = 0;
		}
		--size;
		return Element;
	}
	return 0;
}

Information* List::searchFor(char* key) const {
	ListElement* tmp = first;
	while (tmp != 0) {
		if (tmp->data->equals(key))
			return tmp->data;
		tmp = tmp->next;
	}
	return 0;
}
/*
void List::print() {
	ListElement* tmp = first;
	while (tmp != 0) {
		cout << "\t" << tmp->data << " (" << tmp->data->getLexem()
				<< ")  Hashcode: " << tmp->data->getHashCode() << "\n";
		tmp = tmp->next;
	}
}
*/
