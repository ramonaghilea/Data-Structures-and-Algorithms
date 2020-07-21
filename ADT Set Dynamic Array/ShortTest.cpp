#include "ShortTest.h"
#include <assert.h>
#include "Set.h"
#include "SetIterator.h"

void testAll() { 
	Set s;
	assert(s.isEmpty() == true);
	assert(s.size() == 0); 
	assert(s.add(5)==true);
	assert(s.add(1)==true);
	assert(s.add(10)==true);
	assert(s.add(7)==true);
	assert(s.add(1)==false);
	assert(s.add(10)==false);
	assert(s.add(-3)==true);
	assert(s.size() == 5);
	assert(s.search(10) == true);
	assert(s.search(16) == false);
	assert(s.remove(1) == true);
	assert(s.remove(6) == false);
	assert(s.size() == 4);


	SetIterator it = s.iterator();
	it.first();
	int sum = 0;
	while (it.valid()) {
		TElem e = it.getCurrent();
		sum += e;
		it.next();
	}
	assert(sum == 19);

}

void testIntersection()
{
	Set s1;
	Set s2;
	s1.add(1);
	s1.add(2);
	s1.add(3);
	s1.add(4);

	s2.add(2);
	s2.add(3);

	s1.intersection(s2);
	assert(s1.size() == 2);
	assert(s1.search(1) == false);
	assert(s1.search(2) == true);
	assert(s1.search(3) == true);
	assert(s1.search(4) == false);
}

void testIntersectionNoCommonElements()
{
	Set s1;
	Set s2;
	s1.add(1);
	s1.add(2);
	s1.add(3);
	s1.add(4);

	s2.add(10);
	s2.add(11);

	s1.intersection(s2);
	assert(s1.size() == 0);
	assert(s1.search(1) == false);
	assert(s1.search(2) == false);
	assert(s1.search(3) == false);
	assert(s1.search(4) == false);
}
