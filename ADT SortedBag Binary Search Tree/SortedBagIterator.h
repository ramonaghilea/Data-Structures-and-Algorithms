#pragma once
#include "SortedBag.h"
#include <vector>
#include <iostream>
#include <stack>

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);

	BSTNode* currentElement;
	int frequencyCurrentElement;
	std::stack<BSTNode*> stack{};

public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
};

