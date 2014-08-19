#ifndef LISTELEMENT_H_
#define LISTELEMENT_H_

class Information;

// Container used by the list class in order to store information about a lexeme
class ListElement {

	friend class List;
	friend class Symtable;

    Information* data;
	ListElement* next;

public:

    // Creates a list element
	ListElement();

};

#endif /* LISTELEMENT_H_ */
