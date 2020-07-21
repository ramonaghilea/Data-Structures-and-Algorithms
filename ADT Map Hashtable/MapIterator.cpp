#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;

// complexity: BC = theta(1) WC = theta(m) AC = theta(m) overall O(m)
MapIterator::MapIterator(const Map& d) : map(d)
{
	this->currentElement = 0;

	// search for the first element which is not NULL
	while ((this->map.elements[this->currentElement] == NULL_TELEM || this->map.elements[this->currentElement] == DELETED_TELEM) && this->valid())
		this->currentElement++;
}

// complexity: BC = theta(1) WC = theta(m) AC = theta(m) overall O(m)
void MapIterator::first() {
	this->currentElement = 0;

	// search for the first element which is not NULL
	while ((this->map.elements[this->currentElement] == NULL_TELEM || this->map.elements[this->currentElement] == DELETED_TELEM) && this->valid())
		this->currentElement++;
}

// complexity: BC = theta(1) WC = theta(m) AC = theta(m) overall O(m)
void MapIterator::next() {
	if (this->valid())
		this->currentElement++;
	else
		throw exception("Invalid next.");

	while ((this->map.elements[this->currentElement] == NULL_TELEM || this->map.elements[this->currentElement] == DELETED_TELEM) && this->valid())
		this->currentElement++;
}

// complexity: BC = WC = AC = theta(1) overall theta(1)
TElem MapIterator::getCurrent(){
	if (this->valid())
		return this->map.elements[this->currentElement];
	else 
		throw exception("Invalid getCurrent.");
}

// complexity: BC = WC = AC = theta(1) overall theta(1)
bool MapIterator::valid() const {
	if (this->currentElement < this->map.m && this->currentElement >= 0)
		return true;
	return false;
}

// complexity: BC = theta(1) WC = theta(m) AC = theta(m) overall O(m)
void MapIterator::previous()
{
	if (this->valid())
		this->currentElement--;
	else
		throw exception("Invalid previous.");

	while ((this->map.elements[this->currentElement] == NULL_TELEM || this->map.elements[this->currentElement] == DELETED_TELEM) && this->valid())
		this->currentElement--;
}

// complexity: BC = theta(1) WC = theta(m) AC = theta(m) overall O(m)
void MapIterator::last()
{
	this->currentElement = this->map.m - 1;

	// search for the first element which is not NULL
	while ((this->map.elements[this->currentElement] == NULL_TELEM || this->map.elements[this->currentElement] == DELETED_TELEM) && this->valid())
		this->currentElement--;
}



