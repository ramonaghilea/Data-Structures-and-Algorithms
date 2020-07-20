#include "SMMIterator.h"
#include "SortedMultiMap.h"

// complexity: theta(1)
SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	this->currentElement = this->map.head;
}

// complexity: theta(1)
void SMMIterator::first(){
	this->currentElement = this->map.head;
}

// complexity: theta(1)
void SMMIterator::next(){
	exception invalidElement;
	if (this->currentElement == NULL)
		throw invalidElement;

	this->currentElement = this->currentElement->next;
}

// complexity: theta(1)
bool SMMIterator::valid() const{
	if (this->currentElement != NULL)
		return true;
	return false;
}

// complexity: theta(1)
TElem SMMIterator::getCurrent() const{
	exception invalidElement;
	if (this->currentElement == NULL)
		throw invalidElement;

	return this->currentElement->info;
}


