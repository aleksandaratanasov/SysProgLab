#ifndef _LISTT_
#define _LISTT_

template<class T>
class ListTElement;
template<class T>
class ListT;

template<class T>
class ListTElement {

    unsigned long index;
    T* data;
    ListTElement<T>* next;

  public:
    ListTElement<T>() : index(0), data(0), next(0) {}

    ~ListTElement<T>() {
      if(data)
        delete data;
    }

    void setIndex(unsigned long index) {
      this->index = index;
    }

    unsigned long getIndex() {
      return index;
    }

    void setData(T* data) {
      this->data = data;
    }

    T* getData() {
      return data;
    }

    void setNext(ListTElement<T>* next) {
      this->next = next;
    }

    ListTElement<T>* getNext() {
      return next;
    }
};

template <class T>
class ListT {

    ListTElement<T>* first;
    ListTElement<T>* last;
    unsigned long size;

  public:
    ListT<T>() : first(0), last(0), size(0) {}

    ~ListT<T>() {
      while(first)
        removeFirst();
    }

    void setFirst(ListTElement<T>* first) {
      this->first = first;
    }

    ListTElement<T>* getFirst() {
      return first;
    }

    void setLast(ListTElement<T>* last) {
      this->last = last;
    }

    ListTElement<T>* getLast() {
      return last;
    }

    unsigned long getSize() {
      return size;
    }

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

    T* searchFor(unsigned long index) const {
      ListTElement<T>* tmp = first;
      while (tmp) {
          if (tmp->getIndex() == index)
              return tmp->getData();
          tmp = tmp->getNext();
      }
      return 0;
    }

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
