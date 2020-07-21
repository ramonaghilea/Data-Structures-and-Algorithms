#include "MatrixIterator.h"
#include <exception>

using namespace std;

// Complexity: BC = WC = AC = theta(1) overall = theta(1)
MatrixIterator::MatrixIterator(const Matrix& matrix) : matrix(matrix)
{
	this->currentLine = 0;
	this->currentColumn = 0;
}

// Complexity: BC = WC = AC = theta(1) overall = theta(1)
void MatrixIterator::first()
{
	this->currentLine = 0;
	this->currentColumn = 0;
}

// Complexity: BC = WC = AC = theta(1) overall = theta(1)
void MatrixIterator::next()
{
	if (this->currentColumn == -1 && this->currentLine == -1)
		return;

	this->currentColumn++;

	if (this->currentColumn >= this->matrix.nrColumns())
	{
		this->currentLine++;

		if (this->currentLine >= this->matrix.nrLines())
		{
			// not valid
			this->currentColumn = -1;
			this->currentLine = -1;
		}
		else
			this->currentColumn = 0;
	}
}

// Complexity: BC = theta(1) WC = theta(n) AC = theta(n) overall = O(n)
TElem MatrixIterator::getCurrent()
{
	if (this->currentColumn == -1 && this->currentLine == -1)
		throw exception("Invalid getCurrent");

	return this->matrix.element(this->currentLine, this->currentColumn);
}

// Complexity: BC = WC = AC = theta(1) overall = theta(1)
bool MatrixIterator::valid() const
{
	if (this->currentLine < 0 || this->currentColumn < 0 || this->currentLine >= this->matrix.nrLines() || this->currentColumn >= this->matrix.nrColumns())
		return false;

	return true;
}
