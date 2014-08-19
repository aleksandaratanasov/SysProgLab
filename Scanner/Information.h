#ifndef INFORMATION_H_
#define INFORMATION_H_

// Data container that represents a token read from a source file
class Information {

	char* lexem;
	int ttype;
	unsigned int hashcode;

public:

	/** Erzeugt ein neues Information-Objekt.
	 * <p>
	 * Der Inhalt von lexem wird <b>kopiert</b> und nicht referenziert!
	 *
	 */
    // Creates information
    // Note: lexeme is copied and not just referenced in order to preserve it for further use
	Information();

    // Creates information given a lexem, its length, type and hashcode
	Information(char* lexem, int length, int ttype, unsigned int hashcode);

    // Initializes the content of information
	void initialize(char* lexem, int length, int ttype, unsigned int hashcode);

    // Returns hashcode of the lexeme stored inside information
	unsigned int getHashCode();

	~Information();

    // Returns the lexeme stored inside information by reference
	char* getLexem();

	/** vergleicht, ob das übergebene lexem dem im Objekt gespeicherten lexem entspricht.
	 * @return <b>True</b> wenn sie sie übereinstimmen, sonst <b>false</b>;
	 */
    // Checks if a given lexeme is equal to the one stored in information
    // Returns true if equal
	bool equals(char* lexem);

    // Returns the type of the lexeme
	int getType();
	
	void toArray();
};

#endif /* INFORMATION_H_ */
