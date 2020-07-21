#include "Set.h"
#include "SetITerator.h"


Set::Set() {
	this->nrElements = 0;
	this->capacity = 20;
	this->elementsArray = new TElem[this->capacity];
}

// complexity: O(n)
Set::Set(const Set& copySet)
{
	this->capacity = copySet.capacity;
	this->nrElements = copySet.nrElements;
	this->elementsArray = new TElem[this->capacity];

	for (int i = 0; i < this->nrElements; i++)
		this->elementsArray[i] = copySet.elementsArray[i];
}

// complexity: O(n)
Set& Set::operator=(const Set& copySet)
{
	if (this == &copySet)
		return *this;

	this->capacity = copySet.capacity;
	this->nrElements = copySet.nrElements;
	this->elementsArray = new TElem[this->capacity];

	delete[] this->elementsArray;
	for (int i = 0; i < this->nrElements; i++)
		this->elementsArray[i] = copySet.elementsArray[i];

	return *this;
}

// complexity: O(n) (it adds the element to the end, but first it calls search() (O(n)) in order to check if the element already exists)
bool Set::add(TElem elem) {
	if (this->capacity == this->nrElements)
	{
		// we have to resize the array because it is full
		this->capacity = this->capacity * 2;
		TElem* newElementsArray = new TElem[this->capacity];

		// copy the existing elements to the new array
		for (int i = 0; i < this->nrElements; i++)
		{
			newElementsArray[i] = this->elementsArray[i];
		}
		//deallocate the memory for the previous array
		delete[] this->elementsArray;
		this->elementsArray = newElementsArray;
	}

	if (!this->search(elem))
	{
		// if the element does not already exist we add it
		this->elementsArray[this->nrElements] = elem;
		this->nrElements++;
		return true;
	}

	return false;
}

// complexity: O(n)
bool Set::remove(TElem elem) {
	if (this->search(elem))
	{
		//the element exists in the set
		// search for the position of the element
		int position;
		for (int i = 0; i < this->nrElements; i++)
		{
			if (this->elementsArray[i] == elem)
			{
				position = i;
			}
		}
		for (int i = position; i < this->nrElements - 1; i++)
		{
			this->elementsArray[i] = this->elementsArray[i + 1];
		}
		this->nrElements--;
		return true;

		// check if the array is only a quarter full and resize it to half of its capacity
		if (this->nrElements < this->capacity / 4)
		{
			this->capacity = this->capacity / 2;
			TElem* newElementsArray = new TElem[this->capacity];

			// copy the existing elements to the new array
			for (int i = 0; i < this->nrElements; i++)
			{
				newElementsArray[i] = this->elementsArray[i];
			}
			//deallocate the memory for the previous array
			delete[] this->elementsArray;
			this->elementsArray = newElementsArray;
		}
	}
	return false;
}

// complexity: O(n)
bool Set::search(TElem elem) const {
	for (int i = 0; i < this->nrElements; i++)
	{
		if (this->elementsArray[i] == elem)
		{
			return true;
		}
	}
	return false;
}

// complexity: theta(1)
int Set::size() const {
	return this->nrElements;
}

// complexity: theta(1)
bool Set::isEmpty() const {
	if (this->nrElements == 0)
	{
		return true;
	}
	return false;
}


Set::~Set() {
	delete[] this->elementsArray;
}

void Set::intersection(const Set& s)
{
	for (int i = 0; i < this->nrElements; i++)
	{
		if (!s.search(this->elementsArray[i])) // if the element is not in the set s, we remove it
		{
			this->remove(this->elementsArray[i]);
			i--; // the element on the i th position will be removed, so we need to consider the current element on the
			// i th position
		}
	}
}

// complexity: theta(1)
SetIterator Set::iterator() const {
	return SetIterator(*this);
}


