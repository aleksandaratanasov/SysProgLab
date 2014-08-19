#ifndef OBJECTCONTAINER_H_
#define OBJECTCONTAINER_H_

// This template class allows the creation of bulks of a specific class (multiple instances of the same class)
// in order to speed up the overall process. The advantage of creating multiple instances with a single step is
// that we avoid accessing the memory multiple times
// Note: all instances of the specified class are stored in an array. Once the container no longer contains any
// NEW instances, a new container is generated with the same size (chain) and the references are taken from there
#include <iostream>

template<class type>

class ObjectContainer {


	type* data;
	ObjectContainer<type>* next;
	unsigned int count;
	unsigned int inititalSize;

	static ObjectContainer<type>* last;

public:

    // Creates an object containre with a given size of the single segments
	ObjectContainer(unsigned int intitalSize);

    // Deletes the container and all containers chained to it. All objects stored are deleted
    ~ObjectContainer();

    // Returns a reference to an unused element inside the container
    type* newObject();

};

template<class type>

ObjectContainer<type>* ObjectContainer<type>::last = 0;

template<class type>

ObjectContainer<type>::ObjectContainer(unsigned int initialSize) {
	this->inititalSize = initialSize;
	data = new type[initialSize];
	count = 0;
	last = this;
	next = 0;
}

template<class type>

ObjectContainer<type>::~ObjectContainer() {
	delete[] data;
	if (next != 0) {
		delete next;
	}
}

template<class type>

type* ObjectContainer<type>::newObject() {
	if (count < inititalSize) {
		return &(data[count++]);
	}

	if (next == 0) {
		next = new ObjectContainer<type>(inititalSize);
	}

	return last->newObject();
}

#endif /* OBJECTCONTAINER_H_ */
