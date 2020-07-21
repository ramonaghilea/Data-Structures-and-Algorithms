#pragma once

#define NULL_TELEM -11111
typedef int TElem;
class SetIterator;

class Set {
	friend class SetIterator;

    private:
        int nrElements;
        int capacity;
        TElem* elementsArray;


    public:
        //implicit constructor
        Set();

        //copy constructor
        Set(const Set& copySet);

        //assignment operator
        Set& operator=(const Set& copySet);

        //adds an element to the set
		//returns true if the element was added, false otherwise (if the element was already in the set and it was not added)
        //resizes the array (double its capacity) if the array is full (before adding)
        // complexity: O(n) (it adds the element to the end, but first it calls search() (O(n)) in order to check if the element already exists)
        bool add(TElem e);

        //removes an element from the set
		//returns true if e was removed, false otherwise
        //resizes the array (to the half of its capacity) if the array is only a quarter full (after removing)
        // complexity: O(n)
        bool remove(TElem e);

        //checks whether an element belongs to the set or not
        // complexity: O(n)
        bool search(TElem elem) const;

        //returns the number of elements
        // complexity: theta(1)
        int size() const;

        //check whether the set is empty or not
        // complexity: theta(1)
        bool isEmpty() const;

        //return an iterator for the set
        // complexity: theta(1)
        SetIterator iterator() const;

        // destructor
        ~Set();

        //keeps only the elements which appear in s as well
        void intersection(const Set& s);
};





