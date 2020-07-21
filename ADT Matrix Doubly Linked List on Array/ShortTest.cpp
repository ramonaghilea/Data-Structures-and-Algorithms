#include <assert.h>
#include "Matrix.h"
#include <iostream>
#include "MatrixIterator.h"

using namespace std;

void testAll() { 
	Matrix m(4, 4);
	assert(m.nrLines() == 4);
	assert(m.nrColumns() == 4);	
	m.modify(1, 1, 5);
	assert(m.element(1, 1) == 5);
	TElem old = m.modify(1, 1, 6);
	assert(m.element(1, 2) == NULL_TELEM);
	assert(old == 5);
}

void add5()
{
	Matrix m(10, 10);
	for (int j = 0; j < m.nrColumns(); j++)
	{
		m.modify(0, j, 3);
		m.modify(1, j, 4);
	}
	for (int j = m.nrColumns()-1; j >= 0 ; j--)
	{
		m.modify(4, j, 3);
		m.modify(5, j, 4);
	}

	for (int j = m.nrColumns() - 1; j >= 0; j--)
	{
		assert(m.element(4, j) == 3);
		assert(m.element(5, j) == 4);
	}
	for (int i = 0; i < m.nrLines() - 1; i++)
	{
		m.modify(i, 1, 0);
		m.modify(i + 1, 3, 0);
		assert(m.element(i, 1) == 0);
	}
	for (int j = m.nrColumns() - 1; j >= 0; j--)
	{
		m.modify(4, j, 0);
	}

	for (int j = m.nrColumns() - 1; j >= 0; j--)
	{
		assert(m.element(4, j) == 0);
	}
}

void testIterator()
{
	Matrix m(4, 4);
	m.modify(0, 1, 5);
	MatrixIterator im = m.iterator();

	assert(im.getCurrent() == 0);
	im.next();
	assert(im.getCurrent() == 5);
	for (int i = 0; i <= m.nrColumns() * m.nrLines() - 2; i++)
		im.next();
	try
	{
		im.getCurrent();
		assert(false);
	}
	catch (exception&)
	{
		assert(true);
	}
}
void testIterator2()
{
	Matrix m(5, 5);
	MatrixIterator im = m.iterator();
	m.modify(0, 0, 5);
	m.modify(3, 3, 2);

	assert(im.getCurrent() == 5);
	for (int i = 0; i <= m.nrColumns() * m.nrLines() - 1; i++)
		im.next();

	try
	{
		im.getCurrent();
		assert(false);
	}
	catch (exception&)
	{
		assert(true);
	}
}