#pragma once
#include "Map.h"
class MapIterator
{
	friend class Map;
private:
	const Map& map;
	int currentElement;

	MapIterator(const Map& m);
public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
	//changes the current element from the iterator to the previous element, or, if the current element was the first, makes the iterator invalid
	//throws an exception if the iterator is not valid
	void previous();
	void last();
};


