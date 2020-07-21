#pragma once
#include "Set.h"

class SetIterator
{
	friend class Set;
private:
	const Set& set;
	SetIterator(const Set& s);

	int currentElement;

public:
	//sets the current element from the iterator to the first element of the container
	void first();

	//moves the current element from the container to the next element if there are elements left (if the iterator is valid)
	void next();

	//returns the current element from the iterator
	//returns NULL_TELEM if the iterator is not valid
	TElem getCurrent();

	//verifies if the iterator is valid (if it points to a valid element from the container)
	bool valid() const;
};


