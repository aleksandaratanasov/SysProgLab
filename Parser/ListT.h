#ifndef _LISTT_
#define _LISTT_

template<class T>
class ListTElement;
template<class T>
class ListT;

template<class T>
class ListTElement {
    friend class ListT<T>;

    unsigned long index;
    T* data;  // Prog, Statements, Statement, Decls, Decl etc.
    ListTElement<T>* next;

  public:
    ListTElement<T>();
    ~ListTElement<T>();
};

template<class T>
ListTElement<T>::ListTElement() : index(0), data(0), next(0) {
}

template<class T>
ListTElement<T>::~ListTElement() {
  if(data)
    delete data;
}

template <class T>
class ListT {
    friend class ListTElement<T>;

    ListTElement<T>* first;
    ListTElement<T>* last;
    unsigned long size;

  public:
    ListT<T>() : first(0), last(0), size(0) {
    }
    ~ListT<T>() {
      //FIXME not working properly
      while(first)
        removeFirst();
    }

    void removeFirst() {
      if (first) {
          ListTElement<T>* el = first;
          first = first->next; // go to the next element
          if (!first) // no elements left
              last = 0;
          delete el;
          --size;
      }
    }

    void append(T* data) {
      ListTElement<T>* el = new ListTElement<T>();
      el->data = data;
      el->index = size;

      if (!first)
          first = el;
      else
          last->next = el;
      last = el;
      ++size;
    }

    T* searchFor(unsigned long index) const {
      ListTElement<T>* tmp = first;
      while (tmp) {
          if (tmp->index == index)
              return tmp->data;
          tmp = tmp->next;
      }
      return 0;
    }

    void print() {
      ListTElement<T>* tmp = first;
      while (tmp) {
        std::cout << tmp->index << " ";
        tmp = tmp->next;
      }
      std::cout << std::endl;
    }
};

//template<class T>
//ListT<T>::ListT() {
//  first = last = 0;
//  size = 0;
//}

//template<class T>
//ListT<T>::~ListT() {
//  while(first->next)
//    removeFirst();
//}

//template<class T>
//ListTElement<T>* ListT<T>::removeFirst() {
//  if (first != 0) {
//      ListTElement<T>* el = first;
//      first = first->next;
//      if (!first)
//          last = 0;
//      --size;
//      return el;
//  }
//  return 0;
//}

//template<class T>
//void ListT<T>::append(T* data) {
//  ListTElement<T> el = new ListTElement<T>();
//  el.data = data;
//  el.index = size;

//  if(!size)
//    first = last = el;
//  else
//    last->next = el;

//  size++;
//}

//template<class T>
//ListTElement<T>* ListT<T>::searchFor(unsigned long key) const {
//  ListTElement<T>* tmp = first;
//  while (tmp != 0) {
//      if (tmp->data->equals(key))
//          return tmp->data;
//      tmp = tmp->next;
//  }
//  return 0;
//}

#endif
