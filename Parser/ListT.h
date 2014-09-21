#ifndef _LISTT_
#define _LISTT_

template<class T>
class ListTElement;
template<class T>
class ListT;

/*!
 * \brief ListTElement is the basic component of ListT. It contains a generic piece of information (data), an index and a link to its successor
 */
template<class T>
class ListTElement {

    //! Unique identifier of the element
    unsigned long index;
    //! Generic piece of information that is determined by the type used during the declaration of the element
    T* data;
    //! Link to the successor of the current element. If T is an abstract class, the successor need not be of the same type although all elements of different types has to be derived from the same abstract class
    ListTElement<T>* next;

  public:
    //! Initializing all members of the element
    ListTElement<T>() : index(0), data(0), next(0) {}

    //! Deletes the generic piece of information if any is stored inside the element
    ~ListTElement<T>() {
      if(data)
        delete data;
      next = 0;
    }

    //! Sets the index of the element. In order to keep it unique it is advisable to leave the generation and setting of the index to an automated routine
    void setIndex(unsigned long index) {
      this->index = index;
    }

    //! Retrieves the index of the element
    unsigned long getIndex() {
      return index;
    }

    //! Sets the generic piece of information
    void setData(T* data) {
      this->data = data;
    }

    //! Retrieves the generic piece of information stored in the element
    T* getData() {
      return data;
    }

    //! Sets the successor of the element
    void setNext(ListTElement<T>* next) {
      this->next = next;
    }

    //! Retrieves the successor of the element
    ListTElement<T>* getNext() {
      return next;
    }
};

/*!
 * \brief ListT is a single-linked list structure that uses ListTElement as a basic component to store information (see ListTElement for more information)
 */
template <class T>
class ListT {

    //! Points at the head of the list (very first element)
    ListTElement<T>* first;
    //! Points at the tail of the list (very last element)
    ListTElement<T>* last;
    //! Number of elements in the list
    unsigned long size;

  public:
    //! Initializes all members of the list
    ListT<T>() : first(0), last(0), size(0) {}

    //! Removes all elements in the list
    ~ListT<T>() {
      while(first)
        removeFirst();
    }

    //! Set the list's head
    void setFirst(ListTElement<T>* first) {
      this->first = first;
    }

    //! Retrieves the list's head
    ListTElement<T>* getFirst() {
      return first;
    }

    //! Sets the list's tail
    void setLast(ListTElement<T>* last) {
      this->last = last;
    }

    //! Retrieves the list's tail
    ListTElement<T>* getLast() {
      return last;
    }

    //! Retrieves the list's size (only number of elements, not the memory allocated!)
    unsigned long getSize() {
      return size;
    }

    //! Removes the head of the list and sets its successor as the new one
    //! Used by the destructor for a recursive deletion of all elements in the list
    void removeFirst() {
      if (first) {
          ListTElement<T>* el = first;
          first = first->getNext(); // go to the next element
          if (!first) // no elements left
              last = 0;
          delete el;
          --size;
      }
    }

    //! Creates a new element using a given generic piece of information and add it to the end of the list
    void append(T* data) {
      ListTElement<T>* el = new ListTElement<T>();
      el->setData(data);
      el->setIndex(size);

      if (!first)
          first = el;
      else
          last->setNext(el);
      last = el;
      ++size;
    }

    //! Locates an element based on its index. Due to the possibility that the list may contain elements of various
    //! types derived from a superclass this is the only way to look for a specific element. If there are two or
    //! more elements with the same index (can happen only if user assigns those manually), the first element encountered
    //! that satisfies the search criterion is returned and the rest neglected
    T* searchFor(unsigned long index) const {
      ListTElement<T>* tmp = first;
      while (tmp) {
          if (tmp->getIndex() == index)
              return tmp->getData();
          tmp = tmp->getNext();
      }
      return 0;
    }

    //! Displays all elements in the list
    void print() {
      ListTElement<T>* tmp = first;
      while (tmp) {
        std::cout << tmp->getIndex() << " ";
        tmp = tmp->getNext();
      }
      std::cout << std::endl;
    }
};

#endif
