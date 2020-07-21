#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

// complexity
// BC = theta(1), the bag has 1 element or only equal elements
// AV = theta(log2n)
// WC = theta(n), if the BST is a degenerate one
// overall = O(n)
SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	BSTNode* node = this->bag.root;

	while (node != NULL)
	{
		this->stack.push(node);
		node = node->left;
	}

	// this->currentElement will point to the leftmost element (the first one)
	if (!this->stack.empty())
	{
		this->currentElement = this->stack.top();
	}
	else
		this->currentElement = NULL;

	this->frequencyCurrentElement = 1;
}

// complexity
// BC = WC = AC = theta(1)
// overall = theta(1)
TComp SortedBagIterator::getCurrent() {
	exception invalidElement;
	if (this->currentElement == NULL)
		throw invalidElement;

	return this->currentElement->info.first;
}

// complexity
// BC = WC = AC = theta(1)
// overall = theta(1)
bool SortedBagIterator::valid() {
	if (this->currentElement != NULL)
		return true;
	return false;
}

// complexity
// BC = theta(1), if the element has been already visited through the iterator
// AV = theta(log2n)
// WC = theta(n), if the root has a right child and the left subtree is a degenerate tree
// overall = O(n)
void SortedBagIterator::next() {

	exception invalidElement;
	if (this->currentElement == NULL)
		throw invalidElement;

	if (this->frequencyCurrentElement < this->currentElement->info.second)
	{
		// currentElement will point to the same node
		// increase the frequency
		this->frequencyCurrentElement++;
	}
	else
	{
		BSTNode* node = this->stack.top();
		this->stack.pop();

		if (node->right != NULL)
		{
			node = node->right;

			while (node != NULL)
			{
				this->stack.push(node);
				node = node->left;
			}
		}
		if (!this->stack.empty())
		{
			this->currentElement = this->stack.top();
		}
		else
			this->currentElement = NULL;

		this->frequencyCurrentElement = 1;
	}
}

// complexity
// BC = theta(1), the bag has 1 element or only equal elements
// AV = theta(log2n)
// WC = theta(n), if the BST is a degenerate one
// overall = O(n)
void SortedBagIterator::first() {
	// take the leftmost element
	BSTNode* node = this->bag.root;

	while (node != NULL)
	{
		this->stack.push(node);
		node = node->left;
	}

	// this->currentElement will point to the leftmost element(the first one)
	if (!this->stack.empty())
	{
		this->currentElement = this->stack.top();
	}
	else
		this->currentElement = NULL;

	this->frequencyCurrentElement = 1;
}

