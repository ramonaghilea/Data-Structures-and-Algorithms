#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

// complexity: theta(1)
SortedMultiMap::SortedMultiMap(Relation r) {
	this->head = NULL;
	this->relation = r;
}

// complexity: O(n)
void SortedMultiMap::add(TKey c, TValue v) {

	Node* currentNode = this->head;
	Node* previousNode = NULL;

	while (currentNode != NULL && this->relation(currentNode->info.first, c))
	{
		previousNode = currentNode;
		currentNode = currentNode->next;
	}

	if (currentNode != NULL && currentNode->info.first == c)
	{
		// if the key exists, we have to check if the pair (c,v) is not already in the list
		pair<TKey, TValue> searchedPair(c, v);
		while (currentNode != NULL && currentNode->info.first == c)
		{
			if (currentNode->info == searchedPair)
			{
				return;
			}
			previousNode = currentNode;
			currentNode = currentNode->next;
		}
	}
	// after this while, the currentNode->info.first will be a key > c, or if all the keys are < c, it will be NULL
	// (the end of the list)

	Node* newNode = new Node; // allocate memory for the new node

	if (previousNode == NULL)
	{
		// we have to add at the beginning
		newNode->info = pair<TKey, TValue>(c, v);
		newNode->next = this->head;
		this->head = newNode;
	}
	else
	{
		newNode->info = pair<TKey, TValue>(c, v);
		newNode->next = previousNode->next;
		previousNode->next = newNode;
	}
}

// complexity: O(n)
vector<TValue> SortedMultiMap::search(TKey c) const {
	vector<TValue> result;

	Node* currentNode = this->head;

	while (currentNode != NULL)
	{
		if (currentNode->info.first == c)
		{
			// if the key is c, add it to the result vector
			result.push_back(currentNode->info.second);
		}
		currentNode = currentNode->next;
	}

	return result;
}

// complexity: O(n)
bool SortedMultiMap::remove(TKey c, TValue v) {
	Node* currentNode = this->head;
	Node* previousNode = NULL;

	pair<TKey, TValue> searchedPair(c, v);

	while (currentNode != NULL && currentNode->info != searchedPair)
	{
		previousNode = currentNode;
		currentNode = currentNode->next;
	}

	if (currentNode != NULL) // it did not reach the end
	{
		// we have found the pair
		if (previousNode == NULL)
		{
			// the pair is in the head
			this->head = currentNode->next;
			delete currentNode;
		}
		else
		{
			previousNode->next = currentNode->next;
			delete currentNode;
		}
		return true;
	}

	// if the pair was not in the list, return false
    return false;
}

// complexity: theta(1)
int SortedMultiMap::size() const {
	int sizeSMM = 0;
	Node* currentNode = this->head;

	while (currentNode != NULL)
	{
		sizeSMM++;
		currentNode = currentNode->next;
	}

	return sizeSMM;
}

// complexity: theta(1)
bool SortedMultiMap::isEmpty() const {
	if (this->head == NULL)
		return true;

	return false;
}

// BC: theta(n)
// AC: theta(n)
// WC: theta(n)
// overall complexity: theta(n)
void SortedMultiMap::filter(Condition cond)
{
	Node* currentNode = this->head;
	Node* previous = NULL;
	while (currentNode != NULL)
	{
		if (!cond(currentNode->info.second))
		{
			// remove the node
			if (currentNode == this->head)
			{
				remove(currentNode->info.first, currentNode->info.second);
				currentNode = this->head;
			}
			else
			{
				remove(currentNode->info.first, currentNode->info.second);
				currentNode = previous;
			}
		}
		else
		{
			previous = currentNode;
			currentNode = currentNode->next;
		}
	}
}

// complexity: theta(1)
SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

// complexity: theta(n)
SortedMultiMap::~SortedMultiMap() {
	Node* currentNode = this->head;
	Node* previousNode = NULL;

	while (currentNode != NULL)
	{
		previousNode = currentNode;
		currentNode = currentNode->next;
		delete previousNode;
	}
}
