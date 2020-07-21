#pragma once
#include "Matrix.h"

class MatrixIterator
{
	friend class Matrix;

private:
	const Matrix& matrix;
	int currentLine, currentColumn;

public:
	MatrixIterator(const Matrix& matrix);
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
};

