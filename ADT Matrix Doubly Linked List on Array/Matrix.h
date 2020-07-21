#pragma once

typedef int TElem;
#define NULL_TELEM 0
#define INIT_CAPACITY 100

class MatrixIterator;
typedef struct triple
{
	TElem line, column, value;
};

typedef struct Node
{
	triple info;
	int next;
	int prev;
};

class Matrix {
	friend class MatrixIterator;
private:

	Node* nodes;
	int capacity;
	int head;
	int tail;
	int firstEmpty;
	int size;

	int numberLines;
	int numberColumns;
public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

	// resizes the dynamic array
	void resize();

	//creates an iterator over all the elements of the Matrix (no matter if they are NULL_TELEM or not). 
	//The iterator will return the elements by line (first elements of the first line, then from second line, 
	//etc).
	MatrixIterator iterator() const;

};
