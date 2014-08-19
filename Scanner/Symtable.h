#ifndef SYMTABLE_H_
#define SYMTABLE_H_

class List;
class Information;
class ListElement;

template<class type>

class ObjectContainer;

// A symbol table manages the information about all the tokens that were extracted from a source file
class Symtable {

    List* table; // Array of lists
    unsigned int size; // Length of the array of lists
    unsigned int count; // Number of elements inside the whole table
    unsigned int steps; // When resizing the table the new larger size is determined
                        // by the factors steps * table's size + old size
                        // Note: steps also increases
    double maxFill; // Maximum fill amount in percent

	ObjectContainer<Information>* IOC;

	ObjectContainer<ListElement>* LEOC;

    // Alters the size of the table if the fill amount is exceeded
	inline void reorganize();

public:

    // Creates a symbol table given a set of information objects
	Symtable(ObjectContainer<Information>* IOC);

    // Releases the resurved memory for the symbol table and all its elements
	~Symtable();

    // When a new lexem is to be inserted we first check if it isn't already present
    // - if present, no new entry is added and a reference to that element storing it is returned
    // - otherwise a new element is created and added to the table based on a generated hashcode
    //   and a reference to that element is returned
	Information* insert(char* lexem, int length, int ttype);

    // Inserts a set of given keywords and their number into the table; this method is to be called before the
    // actual processing of a given source file starts since keywords are constants
	void insertKeywords(int argv, const char* keywords[]);

    // Searches for a lexem in the table
    // - if lexem is found, a reference to its information is returned
	Information* searchFor(char* lexem);

//	void print();

    // Creates a hashcode for a given lexem, which is then used for insertion in the
    // table and for the hash-entry's identification, where the lexem is stored
	unsigned int createHashcode(char* lexem);

};

#endif /* SYMTABLE_H_ */

