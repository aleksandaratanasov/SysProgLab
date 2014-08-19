#ifndef LIST_H_
#define LIST_H_

class ListElement;
class Information;
class Symtable;

// Single linked list used a basis for the symbol table for resolving collisions where each hash-entry is a separate list
class List {

	friend class Symtable;

	ListElement* first;
	ListElement* last;
	unsigned int size;

    // Removes the first element in the list and returns a pointer to its conent
	ListElement* removeFirst();
	void append(ListElement value);

public:

    // Create an empty list
	List();

	~List();

    // Appends a new element to the end of the list
	void append(ListElement* value);

    // Searches inside the list for a given lexeme
    // - if no element is found, a NULL pointer is returned
    // - otherwise a pointer to the information object that stored given lexeme is returned
    Information* searchFor(char* lexeme) const;

    // TODO: no longer needed; used for printing a list's content
	//void print();
};

#endif /* LIST_H_ */
