#include "SetIterator.h"
#include "Set.h"

// complexity: theta(1)
SetIterator::SetIterator(const Set& m) : set(m)
{
	this->currentElement = 0;
}

// complexity: theta(1)
void SetIterator::first() {
	currentElement = 0;
}

// complexity: theta(1)
void SetIterator::next() {
	if (this->valid())
	{
		currentElement++;
	}
}

// complexity: theta(1)
TElem SetIterator::getCurrent()
{
	if (this->valid())
	{
		return this->set.elementsArray[currentElement];
	}
	return NULL_TELEM;
}

// complexity: theta(1)
bool SetIterator::valid() const {
	if (currentElement < set.nrElements)
	{
		return true;
	}
	return false;
}



