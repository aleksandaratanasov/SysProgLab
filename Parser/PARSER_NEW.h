#ifndef _PARSERNEW_
#define _PARSERNEW_

// NODE
#include <iostream>
#include "../Scanner/Token.h"
#include "../Scanner/Scanner.h"
#include "../Scanner/Information.h"
#include "../Scanner/t_const.h"
#include "../IO/OutBuffer.h"
#include "ListT.h"
// Control types
#define ERROR_TYPE 			999
#define EOF       			2
// Misc node types
#define NO_TYPE 			3
#define ARRAY_TYPE			4
#define INT_TYPE			5
#define OP_PLUS_TYPE		101
#define OP_MINUS_TYPE		102
#define OP_MULT_TYPE		103
#define OP_DIV_TYPE			104
#define OP_LESS_TYPE		105
#define OP_GREAT_TYPE		106
#define OP_EQUAL_TYPE		107
#define OP_NOT_TYPE 		108
#define OP_AND_TYPE			109

class Scanner;
class OutBuffer;
class Information;
template<class T>
class ObjectContainer;
template <class T>
class ListTElement;
template<class T>
class ListT;

class Node;
class ProgNEW;
class DeclsNEW;
class DeclNEW;
class IndexNEW;
class ArrayNEW;
class StatementsNEW;
class StatementNEW;
class ExpNEW;
class Exp2NEW;
class Op_expNEW;
class OpNEW;

// The parser verifies if the parsed tokens are part of a meaningful source code
// (meaningful = obeys the rules of the language's grammar), checks their types
// and finally generates code that is written to an interpreter file, which then
// can be run by an interpreter
// The parsing process is based on a top down parsing tree, where we start from
// from the highest node (Prog) and try to go as deep as possible following a type
// verification
class ParserNEW {

    friend class ListT<Node>;
    static unsigned int depth_counter; // current nesting depth in the source code based
                                       // on the number of opened/closed curly brackets

    ProgNEW* prog;

    void typeCheck();// calls recursively the typeCheck() for each Node
    void makeCode(); // calls recursively the makeCode() for each Node

public:
  // Creates a parser given a scanner and buffer for writing an interpreter file
  ParserNEW(Scanner*, OutBuffer*);

  ~ParserNEW();

};

class Node {
  protected:
    // Error counters for the final statistic. A successful parsing process has to have both equal to 0
    static unsigned int parseErrors;
    static unsigned int typeErrors;

    Scanner* scanner;
    unsigned int line,column;
    long value;
    Information* info;

    // Used for conditional jumps
    static int mark;

    // Error handling
    void parseError(const char* message);
    void typeError(const char* message);

    // Clones token
    void cloneTokenData();
  public:
    unsigned int nodeType;

    Node(Scanner* scanner);
    virtual ~Node();

    virtual void typeCheck() = 0;
    virtual void makeCode(OutBuffer*) = 0;
};

class ProgNEW : public Node {

  DeclsNEW* decls;
  StatementsNEW* statements;

 public:
  ProgNEW(Scanner*, OutBuffer*, int&, int&);
  virtual ~ProgNEW();

  virtual void typeCheck();
  virtual void makeCode(OutBuffer* out);
};

class DeclsNEW : public Node {
    // contains all variable declarations
    // ones we exit the last Decl and enter Statementes
    // typeCheck() and makeCode() are invoked recursively
    // for each element of the list
    ListT<DeclNEW>* decls;

  public:
    DeclsNEW(Scanner*, OutBuffer*, int&, int&);
    virtual ~DeclsNEW();

    virtual void typeCheck();
    virtual void makeCode(OutBuffer* out);
};

class DeclNEW : public Node {

    ArrayNEW* array;

  public:
    DeclNEW(Scanner*, OutBuffer*, int&, int&);
    virtual ~DeclNEW();

    virtual void typeCheck();
    virtual void makeCode(OutBuffer* out);
};

class ArrayNEW : public Node {
  public:
    ArrayNEW(Scanner*, OutBuffer*, int&, int&);
    virtual ~ArrayNEW();

    virtual void typeCheck();
    virtual void makeCode(OutBuffer* out);
};

class StatementsNEW : public Node {

    // NOTE: depthCounter might not be needed after all
    // 1) create statements and store jump mark
    // 2) generate list for each statement (repeat storing jump marks for each if/while
    // 3) after the list generation insert the mark that is stored in the statement
    // when nesting multiple statements (e.g: if(...){ if(...){ ... } }
    // this counter will increase with each "{" token and decrease with
    // each "}" token; top level is depth_counter==0;
    // Each statements block will be stored in a ListT
    // - top level statement is at index 0
    // - each new nested statement is added to the list
    //
    // Example:
    //    if(){         // A
    //      while() {   // B
    //        if() {    // C
    //        }
    //        else {    // D
    //        }
    //      }
    //
    //      if() {      // E
    //      }
    //    }
    //    else {        // F
    //    }
    //
    //  *statements
    //      |
    //      |-------statement[if:A]--{statements
    //      |                             |
    //      |                             |-------statement[while:B]--{statements
    //      |                             |                               |
    //      |                             |                               |----statement[if:C]--{statements[NULL]}
    //      |                             |                               |
    //      |                             |                               |----statement[else:D]--{statements[NULL]}}
    //      |                             |
    //      |                             |-------statement[if:E]--{statements[NULL]}}
    //      |
    //      |------statement[else:F]--{statements[NULL]}
    //
    // This is used in order to invoke makeCode() properly
    // Each call of makeCode() for an if/while inserts a mark and a conditional jump at the beginning of the statement
    // After we are again on the same level of this statement (we have exited all nested ones)
    // meaning we have closed with using "}", the mark from the jump condition is placed and a NOP is added
    ListT<StatementNEW>* statementList;

  public:
    StatementsNEW(Scanner*, OutBuffer*, int&, int&);
    virtual ~StatementsNEW();

    virtual void typeCheck();
    virtual void makeCode(OutBuffer* out);
};

class StatementNEW : public Node {

//    ListT<StatementsNEW>* statementsList;
    int jumpBackMark; // use in a loop to jump back to the loop's condition before the loop's main body
    int jumpForwardMark;  // used both in if and while to skip main body of conditional structure


  public:
    StatementNEW(Scanner*, OutBuffer*, int&, int&);
    virtual ~StatementNEW();

    virtual void typeCheck();
    virtual void makeCode(OutBuffer* out);
};

class ExpNEW : public Node {

    Exp2NEW* exp2;
    Op_expNEW* op_exp;

  public:
    ExpNEW(Scanner*, OutBuffer*, int&, int&);
    virtual ~ExpNEW();

    virtual void typeCheck();
    virtual void makeCode(OutBuffer* out);
};

class Exp2NEW : public Node {
  public:
    Exp2NEW(Scanner*, OutBuffer*, int&, int&);
    virtual ~Exp2NEW();

    virtual void typeCheck();
    virtual void makeCode(OutBuffer* out);
};

class IndexNEW : public Node {
  public:
    IndexNEW(Scanner*, OutBuffer*, int&, int&);
    virtual ~IndexNEW();

    virtual void typeCheck();
    virtual void makeCode(OutBuffer* out);
};

class Op_expNEW : public Node {
  public:
    Op_expNEW(Scanner*, OutBuffer*, int&, int&);
    virtual ~Op_expNEW();

    virtual void typeCheck();
    virtual void makeCode(OutBuffer* out);
};

class OpNEW : public Node {
  public:
    OpNEW(Scanner*, OutBuffer*, int&, int&);
    virtual ~OpNEW();

    virtual void typeCheck();
    virtual void makeCode(OutBuffer* out);
};

#endif
