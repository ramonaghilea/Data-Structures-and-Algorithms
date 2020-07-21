#pragma once
#include <utility>

typedef int TComp;
typedef TComp TElem;
typedef std::pair<TComp, int> TElemPair;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TCOMP -11111;

class SortedBagIterator;

typedef struct BSTNode
{
	TElemPair info;
	BSTNode* left;
	BSTNode* right;
	BSTNode* parent;
} BSTNode;

class SortedBag {
	friend class SortedBagIterator;

private:
	BSTNode* root;
	Relation relation;
	int nrElements;

public:
	//constructor
	SortedBag(Relation r);

	//adds an element to the sorted bag
	void add(TComp e);

	//removes one occurence of an element from a sorted bag
	//returns true if an eleent was removed, false otherwise (if e was not part of the sorted bag)
	bool remove(TComp e);

	//checks if an element appearch is the sorted bag
	bool search(TComp e) const;

	//returns the number of occurrences for an element in the sorted bag
	int nrOccurrences(TComp e) const;

	//returns the number of elements from the sorted bag
	int size() const;

	//returns an iterator for this sorted bag
	SortedBagIterator iterator() const;

	//checks if the sorted bag is empty
	bool isEmpty() const;

	//destructor
	~SortedBag();

	//counts and returns the number of unique elements in the SortedBag
	int uniqueCount() const;

private:
	// return the maximum node from the subtree with root startNode
	BSTNode* getMaximum(BSTNode* startNode);
};