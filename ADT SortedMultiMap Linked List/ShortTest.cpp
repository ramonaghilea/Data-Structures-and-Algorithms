#include <assert.h>

#include "SortedMultiMap.h"
#include "SMMIterator.h"
#include <exception>
#include <vector>


using namespace std;

bool relation1(TKey cheie1, TKey cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll(){
	SortedMultiMap smm = SortedMultiMap(relation1);
	assert(smm.size() == 0);
	assert(smm.isEmpty());
    smm.add(1,2);
    smm.add(1,3);
    assert(smm.size() == 2);
    assert(!smm.isEmpty());
    vector<TValue> v= smm.search(1);
    assert(v.size()==2);
    v= smm.search(3);
    assert(v.size()==0);
    SMMIterator it = smm.iterator();
    it.first();
    while (it.valid()){
    	TElem e = it.getCurrent();
    	it.next();
    }
    assert(smm.remove(1, 2) == true);
    assert(smm.remove(1, 3) == true);
    assert(smm.remove(2, 1) == false);
    assert(smm.isEmpty());
}

bool condition1(TValue v)
{
    if (v % 2 == 0)
        return true;
    return false;
}

bool condition2(TValue v)
{
    if (v == 10)
        return true;
    return false;
}

void testFilter1()
{
    SortedMultiMap smm = SortedMultiMap(relation1);
    assert(smm.size() == 0);
    assert(smm.isEmpty());

    smm.add(1, 2);
    smm.add(10, 13);
    smm.add(11, 6);
    smm.add(27, 10);
    smm.add(11, 23);

    smm.filter(condition1);

    assert(smm.size() == 3);

    smm.filter(condition1);

    assert(smm.size() == 3);

    assert(smm.remove(1, 2) == true);
    assert(smm.remove(11, 6) == true);
    assert(smm.remove(27, 10) == true);
    assert(smm.remove(10, 13) == false);

    assert(smm.isEmpty());
}

void testFilter2()
{
    SortedMultiMap smm = SortedMultiMap(relation1);
    assert(smm.size() == 0);
    assert(smm.isEmpty());

    smm.add(1, 2);
    smm.add(10, 13);
    smm.add(11, 6);
    smm.add(27, 10);
    smm.add(11, 10);

    smm.filter(condition2);

    assert(smm.size() == 2);

    assert(smm.remove(27, 10) == true);
    assert(smm.remove(11, 10) == true);
    assert(smm.remove(1, 2) == false);
    assert(smm.remove(11, 6) == false);

    assert(smm.isEmpty());
}