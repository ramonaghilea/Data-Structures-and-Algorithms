#include "Matrix.h"
#include <exception>
#include <iostream>
#include <string>
#include "MatrixIterator.h"

using namespace std;

// Complexity: BC = WC = AC = theta(n) overall = theta(n)
Matrix::Matrix(int nrLines, int nrCols) {
	   
	if (nrLines <= 0 || nrCols <= 0)
		throw exception("The number of lines and number of columns are invalid.");
	this->numberLines = nrLines;
	this->numberColumns = nrCols;

	this->capacity = INIT_CAPACITY;
	this->size = 0;
	this->nodes = new Node[this->capacity];
	this->head = -1;
	this->tail = -1;

	for (int i = 0; i < this->capacity; i++)
	{
		this->nodes[i].next = i + 1;
		this->nodes[i].prev = i - 1;
		this->nodes[i].info.value = NULL_TELEM;
	}

	this->nodes[this->capacity - 1].next = -1;
	this->nodes[0].prev = -1;
	//this->printArray();
	this->firstEmpty = 0;
}

// Complexity: BC = WC = AC = theta(1) overall = theta(1)
int Matrix::nrLines() const {

	return this->numberLines;
}

// Complexity: BC = WC = AC = theta(1) overall = theta(1)
int Matrix::nrColumns() const {

	return this->numberColumns;
}

// Complexity: BC = theta(1) WC = theta(n) AC = theta(n) overall = O(n)
TElem Matrix::element(int i, int j) const {

	if (i < 0 || i >= this->numberLines || j < 0 || j >= this->numberColumns)
		throw exception("Invalid line and column.");

	int current = this->head;

	while (current != -1 && this->nodes[current].info.line < i)
		current = this->nodes[current].next;

	if(this->nodes[current].info.line == i)
		while(current != -1 && this->nodes[current].info.line == i && this->nodes[current].info.column < j)
			current = this->nodes[current].next;

	if (current != -1 && this->nodes[current].info.line == i && this->nodes[current].info.column == j)
		return this->nodes[current].info.value;

	return NULL_TELEM;
}

// Complexity: BC = theta(1) WC = theta(n) AC = theta(n) overall = O(n)
TElem Matrix::modify(int i, int j, TElem e) {

	if (i < 0 || i >= this->numberLines || j < 0 || j >= this->numberColumns)
		throw exception("Invalid line and column.");

	TElem previousValue = this->element(i, j);

	if (previousValue == NULL_TELEM && e != NULL_TELEM)
	{
		// add
		int currentNode = this->head;
		int currentPos = 0;

		while (currentNode != -1 && currentPos < this->size)
		{
			if (this->nodes[currentNode].info.line > i)
				break;
			if (this->nodes[currentNode].info.line == i)
			{
				if (this->nodes[currentNode].info.column >= j)
					break;
			}
			currentNode = this->nodes[currentNode].next;
			currentPos++;
		}

		if( this->firstEmpty == -1)
		{
			// resize
			this->resize();
		}

		// allocate
		int newElement = this->firstEmpty;
		this->firstEmpty = this->nodes[this->firstEmpty].next;
		this->nodes[newElement].next = -1;
		this->nodes[newElement].prev = -1;

		// place the information
		triple newInfo;
		newInfo.value = e;
		newInfo.line = i;
		newInfo.column = j;
		this->nodes[newElement].info = newInfo;

		if (this->head == -1)
		{
			this->head = newElement;
			this->tail = newElement;
		}
		else if(currentNode == this->head)
		{
			// add before head
			this->nodes[newElement].next = this->head;
			this->nodes[this->head].prev = newElement;
			this->head = newElement;
		}
		else if (currentNode == -1)
		{
			// add after the tail
			this->nodes[newElement].prev = this->tail;
			this->nodes[this->tail].next = newElement;
			this->tail = newElement;
		}
		else
		{
			this->nodes[newElement].next = currentNode;
			this->nodes[newElement].prev = this->nodes[currentNode].prev;
			this->nodes[this->nodes[currentNode].prev].next = newElement;
			this->nodes[currentNode].prev = newElement;
		}
		this->size++;
	}
	else if (previousValue != NULL_TELEM && e == NULL_TELEM)
	{
		// remove
		// search for the position where the element is
		int currentNode = this->head;
		int currentPos = 0;

		while (currentNode != -1 && currentPos < this->size)
		{
			if (this->nodes[currentNode].info.line > i)
				break;
			if (this->nodes[currentNode].info.line == i)
			{
				if (this->nodes[currentNode].info.column >= j)
					break;
			}
			currentNode = this->nodes[currentNode].next;
			currentPos++;
		}

		if (currentNode != -1)
		{
			// it should be different from -1

			if (currentNode == this->head)
			{
				if (this->head == this->tail)
				{
					this->head = -1;
					this->tail = -1;
				}
				else
				{
					this->head = this->nodes[this->head].next;
					this->nodes[this->head].prev = -1;
				}
			}
			else
			{
				if (currentNode == this->tail)
				{
					this->tail = this->nodes[currentNode].prev;
					this->nodes[this->tail].next = -1;
				}
				else
				{
					this->nodes[this->nodes[currentNode].next].prev = this->nodes[currentNode].prev;
					this->nodes[this->nodes[currentNode].prev].next = this->nodes[currentNode].next;
				}

			}
		}
		// add the current node to the list of empty spaces
		this->nodes[currentNode].next = this->firstEmpty;
		this->nodes[this->firstEmpty].prev = currentNode;
		this->firstEmpty = currentNode;

		this->size--;
	}
	else if (previousValue != NULL_TELEM && e != NULL_TELEM)
	{
		// modify
		triple newInfo;
		newInfo.value = e;
		newInfo.line = i;
		newInfo.column = j;

		// search for the position where it should be modified
		int currentNode = this->head;
		int currentPos = 0;

		while (currentNode != -1 && currentPos < this->size)
		{
			if (this->nodes[currentNode].info.line > i)
				break;
			if (this->nodes[currentNode].info.line == i)
			{
				if (this->nodes[currentNode].info.column >= j)
					break;
			}
			currentNode = this->nodes[currentNode].next;
			currentPos++;
		}

		// certainly we found the element on i, j
		this->nodes[currentNode].info = newInfo;
	}

	return previousValue;
}

// Complexity: BC = WC = AC = theta(n) overall = theta(n)
void Matrix::resize()
{
	// resize
	Node* newNodes = new Node[this->capacity * 2];

	for (int i = 0; i < this->capacity; i++)
	{
		newNodes[i] = this->nodes[i];
	}
	for (int i = this->capacity; i < this->capacity * 2 - 1; i++)
	{
		newNodes[i].next = i + 1;
		newNodes[i].prev = i - 1;
		newNodes[i].info.value = NULL_TELEM;
	}

	newNodes[this->capacity].prev = -1; //CHANGE

	newNodes[this->capacity * 2 - 1].next = -1;

	this->nodes = newNodes;

	this->firstEmpty = this->capacity;
	this->capacity = this->capacity * 2;
}

// Complexity: BC = WC = AC = theta(1) overall = theta(1)
MatrixIterator Matrix::iterator() const
{
	return MatrixIterator(*this);
}


