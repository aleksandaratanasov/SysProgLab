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
#define OP_PLUS_TYPE		101 // +
#define OP_MINUS_TYPE		102 // -
#define OP_MULT_TYPE		103 // *
#define OP_DIV_TYPE			104 // /
#define OP_LESS_TYPE		105 // <
#define OP_GREATER_TYPE		106 // >
#define OP_EQUAL_TYPE		107 // =
#define OP_AEQUI_TYPE       108 // <=>
#define OP_NOT_TYPE 		109 // !
#define OP_AND_TYPE			110 // &
// Statement types
#define STATEMENT_ASSIGN    111 // x = 1; or x[2] = 1;
#define STATEMENT_PRINT     112 // print(x);
#define STATEMENT_READ      113 // read(x);
#define STATEMENT_IF_ELSE   114 // if(...) ... else ...; | if(...) {...} else {...};
#define STATEMENT_WHILE     115 // while(...) ...; or while(...) {...};
#define STATEMENT_BLOCK     116 // {...}
// Operation types
#define EXPRESSION_BRACKETS  117 // (...)
#define EXPRESSION_IDENTIFIER 118 // x or x[2]
#define EXPRESSION_INT       119 // 0,1,2...
#define EXPRESSION_NEGATIVE  120 // -x
#define EXPRESSION_NOT       121 // !(x > 2)

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

    // Each top level statement (top level = not inside a {} block) is stored in
    // a list here. Upon calling makeCode() each list-element's makeCode() is
    // called. Each element contains another statementList (see StatementNEW).
    //  - in case of a single statement (e.g. "print(a);") that sublist stores a
    // single element that represents that statement;
    //  - in case of a block statement (e.g. if(...){BLOCK_OF_STATEMENTS}) that
    // sublist contains all top level statements in that block (here top level is
    // the top most level inside the nested block of statements) and so on.
    /*
     *  top level
     *  @-----|
     *        |----print(a);
     *        |----if(a = 10){ ... } else { ... }
     *        |----print(a);
     *
     *  secondary level
     *  @-----|
     *        |----print(a);
     *        |----if(a = 10)
     *        |         |
     *        |         |----@----|
     *        |         |         |-----a = a + 1;
     *        |         |         |-----while(b < 10) { ... }
     *        |         |
     *        |         |----else
     *        |                |
     *        |                |-----a = 99;
     *        |
     *        |----print(a);
     */
    ListT<StatementNEW>* statements;

  public:
    StatementsNEW(Scanner*, OutBuffer*, int&, int&);
    virtual ~StatementsNEW();

    virtual void typeCheck();
    virtual void makeCode(OutBuffer* out);
};

class StatementNEW : public Node {

    int jumpBackMark; // use in a loop to jump back to the loop's condition before the loop's main body
    int jumpForwardMark;  // used both in if and while to skip main body of conditional structure

    // In case of a single statement statement1/2 are used (statement1 is for the if-block, statement2 is for the else-block)
    // In case of multiple statements statements1/2 are used (statement1 is for the if-block, statement2 is for the else-block)
    // Combinations of the above can also be created; multiple statements case is automatically triggered when "{" is detected
    // even if the block surrounded by the curly brackets has just a single statement in it
    StatementNEW* statement1;
//    StatementsNEW* statements1;
    StatementNEW* statement2;
//    StatementsNEW* statements2;
    StatementsNEW* statements;

    IndexNEW* index;
    ExpNEW* exp;
    //ListT<StatementNEW>* statements;

    unsigned int statementType;

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

    ExpNEW* exp;
    Exp2NEW* exp2;
    IndexNEW* index;

    int expressionType;

  public:
    Exp2NEW(Scanner*, OutBuffer*, int&, int&);
    virtual ~Exp2NEW();

    virtual void typeCheck();
    virtual void makeCode(OutBuffer* out);
};

class IndexNEW : public Node {

    ExpNEW* exp;

  public:
    IndexNEW(Scanner*, OutBuffer*, int&, int&);
    virtual ~IndexNEW();

    virtual void typeCheck();
    virtual void makeCode(OutBuffer* out);
};

class Op_expNEW : public Node {

    OpNEW* op;
    ExpNEW* exp;

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
