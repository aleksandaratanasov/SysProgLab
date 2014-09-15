#ifndef _PARSERAST_
#define _PARSERAST_

template<typename T>
class ListElementAST {
    T* data;
    ListElementAST<T>* next;

  public:
    ListElementAST<T>();
};

template <typename T>
class ListAST {
    friend class ListElementAST<T>;

    ListElementAST<T>* first;
    ListElementAST<T>* last;
    unsigned long size;

  public:
    ListAST<T>();
    ~ListAST<T>();

    void append(ListElement<T>* value);
    T* searchFor(unsigned long index) const;
};

template<typename T>
class TreeNode {

private:

    T* data;
    TreeNode<T>* parent;
    ListAST< TreeNode<T>* > children;

public:

    TreeNode(TreeNode<T>* parent, T data);
    ~TreeNode();

    T& getData() const;
    void setData(const T& data);
    void addChild(const T& data);
    void removeChild(const size_t& indx);
    TreeNode<T>* findChild(const T& data) const;
    TreeNode<T>* getChild(const size_t& indx) const;
    TreeNode<T>* getParent() const;
    int getNumChildren() const;

};

#endif
