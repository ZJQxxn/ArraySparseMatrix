//SparseMatrix.h : Declaretion of class:'SparseMatrix' and struct:'MatrixTerm'
#ifndef SPARSE_H
#define SPARSE_H
#include <iostream>
using std::ostream;

//MatrixTerm representing a term of sparse matrix
struct MatrixTerm
{
	int row;
	int colume;
	float value;
	/*
	Compare two matrix terms.Return 1 if current
	ahead of another; 0 if current totally equals
	to another; -1 if current behind another.
	*/
	int _compare(MatrixTerm& another)
	{
		int rowGap = row - another.row;
		int colGap = colume - another.colume;
		//Two terms are same
		if (rowGap == 0 && colGap == 0)
		{
			return 0;
		}
		else
		{
			if (rowGap < 0)
			{
				return 1;
			}
			else if (rowGap == 0)
			{
				if (colGap < 0)
				{
					return 1;
				}
			}
			return -1;
		}
	}

	MatrixTerm operator - ()
	{
		MatrixTerm term;
		term.row = row;
		term.colume = colume;
		term.value = -value;
		return term;
	}
};


//See implementations in SparseMatrix.cpp
class SparseMatrix
{	
private:
	MatrixTerm *termsArray;
	int terms;
	int finish;//Point at the finish index of termsArray
	int rows, columns;
public:
	SparseMatrix();
	SparseMatrix(int rows, int columns, int terms);
	//operations
	void addTerm(int row, int col, float value);
	void addTerm(MatrixTerm &term);
	void prInArray();
	void prInMatrix();
	SparseMatrix transpose();
	SparseMatrix add(SparseMatrix &another);
	SparseMatrix minus(SparseMatrix &another);
	SparseMatrix multiply(float num);
	//TODO:
	//SparseMatrix multiply(SparseMatrix &another);
};

#endif