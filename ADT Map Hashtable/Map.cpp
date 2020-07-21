#include "Map.h"
#include "MapIterator.h"

#include <stdlib.h>

#include <iostream>

using namespace std;

 int Map::hashFunction(TKey c, TProbeNumber i) const
{
	int intermediateResult = abs(c) % this->m + 0.5 * i + 0.5 * i * i;
	int result = intermediateResult % this->m;
	return result;
}

 // complexity: BC = WC = AC = theta(m) overall theta(m)
Map::Map() {
	this->m = 8;
	this->n = 0;
	this->elements = new TElem[this->m];

	// initialize the elements with NULL_TELEM
	for (int i = 0; i < this->m; i++)
		this->elements[i] = NULL_TELEM;
}

// complexity: BC = theta(m) WC = theta(m^2) AC = theta(m) overall O(m^2)
// the WC is given by the addition of elements in the new dynamic array
void Map::resizeRehash()
{
	// modify the capacity
	this->m *= 2;

	TElem* newElements = new TElem[this->m];

	// initialize the elements with NULL_TELEM
	for (int index = 0; index < this->m; index++)
		newElements[index] = NULL_TELEM;

	for (int index = 0; index < this->m/2; index++)
	{
		// add each element from the previous table to the new table and compute the new hashfunction
		int i = 0;
		int pos = this->hashFunction(this->elements[index].first, i);
		while (i < this->m && newElements[pos] != NULL_TELEM && newElements[pos].first != this->elements[index].first)
		{
			// search until you find a pos that has never been occupied or where the element has been deleted
			i++;
			pos = this->hashFunction(this->elements[index].first, i);
		}
		newElements[pos] = this->elements[index];
	}

	// delete the old table
	delete[] this->elements;
	// replace the old table with the new one
	this->elements = newElements;
}

Map::~Map() {

	delete[] this->elements;
}

// complexity: BC = theta(1) WC = theta(m) AC = theta(1) overall O(m)
// the average case is theta(1) because the load factor(n/m) is < 1
// when resize is needed, the complexity becomes the complexity of the resize function
// (can reach theta(m^2), but rarely)
TValue Map::add(TKey c, TValue v){

	TValue previousValue = NULL_TVALUE;
	int i = 0;
	int pos = this->hashFunction(c, i);

	while (i < this->m && this->elements[pos] != NULL_TELEM && this->elements[pos] != DELETED_TELEM && this->elements[pos].first != c)
	{
		// search until you find a pos that has never been occupied or where the element has been deleted
		i++;
		pos = this->hashFunction(c, i);
	}

	if (i == this->m)
	{
		// resize and rehash
		this->resizeRehash();

		int i = 0;
		int pos = this->hashFunction(c, i);

		while (i < this->m && this->elements[pos] != NULL_TELEM && this->elements[pos] != DELETED_TELEM && this->elements[pos].first != c)
		{
			// search until we find a pos that has never been occupied or where the element has been deleted
			i++;
			pos = this->hashFunction(c, i);
		}

		pair<TKey, TValue> newPair(c, v);
		this->elements[pos] = newPair;
	}
	else
	{
		// memorize the previous value, as we need to return it at the end
		if (this->elements[pos] == DELETED_TELEM)
			previousValue = NULL_TVALUE;
		else
			previousValue = this->elements[pos].second;

		pair<TKey, TValue> newPair(c, v);
		this->elements[pos] = newPair;
	}

	if(previousValue == NULL_TVALUE)
		this->n++; //increase the actual size

	return previousValue;
}

// complexity: BC = theta(1) WC = theta(m) AC = theta(1) overall O(m)
// the average case is theta(1) because the load factor(n/m) is < 1
TValue Map::search(TKey c) const{
	int i = 0;
	int pos = this->hashFunction(c, i);

	while (i < this->m && this->elements[pos] != NULL_TELEM && this->elements[pos].first != c)
	{
		// search until you find a pos that has never been occupied
		// if a pos which has previously been occupied is found, the searching keeps going
		i++;
		pos = this->hashFunction(c, i);
	}

	if (this->elements[pos].first == c)
	{
		// we have found the element
		return this->elements[pos].second;
	}

	// if it is NULL_VALUE or the pair has been deleted previously, return NULL_VALUE
	return NULL_TVALUE;
}

// complexity: BC = theta(1) WC = theta(m) AC = theta(1) overall O(m)
// the average case is theta(1) because the load factor(n/m) is < 1
TValue Map::remove(TKey c){
	int i = 0;
	int pos = this->hashFunction(c, i);

	while (i < this->m && this->elements[pos] != NULL_TELEM && this->elements[pos].first != c)
	{
		// search until you find a pos that has never been occupied
		i++;
		pos = this->hashFunction(c, i);
	}

	if (this->elements[pos].first == c)
	{
		// memorize the previous value, as we need to return it at the end
		TValue previousValue = this->elements[pos].second;

		this->elements[pos] = DELETED_TELEM; // we have found the element, mark the pos as deleted
		this->n--; // decrease the actual size

		return previousValue;
	}
	
	// if it is NULL_VALUE or the pair has been deleted previuosly, return NULL_VALUE
	return NULL_TVALUE;
}

// complexity: BC = WC = AC = theta(1) overall theta(1)
int Map::size() const {

	return this->n;
}

// complexity: BC = WC = AC = theta(1) overall theta(1)
bool Map::isEmpty() const{

	if (this->n == 0)
		return true;
	return false;
}

// complexity: BC = WC = AC = theta(1) overall theta(m)
MapIterator Map::iterator() const {
	return MapIterator(*this);
}



