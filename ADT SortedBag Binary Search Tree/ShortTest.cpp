#include "ShortTest.h"
#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <assert.h>

bool relation1(TComp e1, TComp e2) {
	return e1 <= e2;
}

void testAll() {
	SortedBag sb(relation1);
	sb.add(5);
	sb.add(6);
	sb.add(0);
	sb.add(5);
	sb.add(10);
	sb.add(8);

	assert(sb.size() == 6);
	assert(sb.nrOccurrences(5) == 2);

	assert(sb.remove(5) == true);
	assert(sb.size() == 5);

	assert(sb.search(6) == true);
	assert(sb.isEmpty() == false);

	SortedBagIterator it = sb.iterator();
	assert(it.valid() == true);
	while (it.valid()) {
		it.getCurrent();
		it.next();
	}
	assert(it.valid() == false);
	it.first();
	assert(it.valid() == true);
}

void testUniqueCount1()
{
	SortedBag sb(relation1);
	sb.add(5);
	sb.add(6);
	sb.add(0);
	sb.add(5);
	sb.add(10);
	sb.add(8);

	assert(sb.uniqueCount() == 5);

	sb.remove(8);
	assert(sb.uniqueCount() == 4);

	sb.remove(5);
	assert(sb.uniqueCount() == 4);
}

void testUniqueCount2()
{
	SortedBag sb(relation1);
	sb.add(5);
	sb.add(5);
	sb.add(5);
	sb.add(5);

	assert(sb.uniqueCount() == 1);

	sb.remove(5);
	assert(sb.uniqueCount() == 1);

	sb.remove(5);
	assert(sb.uniqueCount() == 1);

	sb.remove(5);
	sb.remove(5);
	assert(sb.uniqueCount() == 0);
}
