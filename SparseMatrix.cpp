//SparseMatrix.cpp : Implementation of class:'SparseMatrix'
#include "SparseMatrix.h"
#include <algorithm>
using std::cout;
using std::endl;
using std::sort;


//Constructor
SparseMatrix::SparseMatrix()
	:rows(0)
	, columns(0)
	, terms(0)
{

}

SparseMatrix::SparseMatrix(int rows,int columns,int terms)
	:rows(rows)
	,columns(columns)
	, terms(terms)
{
	termsArray = new MatrixTerm[terms];
	finish = -1;
}


//Operations
/*
	Add a term into the matrix
	
	Parameter:row	int  Row of term.
	Parameter:col  int  Column of term
	Parameter:value	  float  Value of term
	
	Return:void
*/
void SparseMatrix::addTerm(int row, int col, float value)
{
	//Matrix full
	if (finish == terms - 1)
	{
		cout << "Matrix is full!" << endl;
		return;
	}

	MatrixTerm term;
	term.row = row;
	term.colume = col;
	term.value = value;
	int index = finish;
	for (; index >= 0; index--)
	{
		//Move backward
		if (term._compare(termsArray[index]) > 0)
		{
			termsArray[index + 1] = termsArray[index];
		}
		//Find correct location
		else if (term._compare(termsArray[index]) < 0)
		{
			break;
		}
		//Avoid store same value
		else if (term._compare(termsArray[index]) == 0)
		{
			return;
		}
	}
	termsArray[index + 1] = term;
	finish++;
}

/*
	Add a term into matrix.

	Parameter:term	MatrixTerm	Term you want to add.

	Return:void
*/
void SparseMatrix::addTerm(MatrixTerm &term)
{
	int row = term.row;
	int col = term.colume;
	float value = term.value;
	addTerm(row, col, value);
}

/*
	Transpose a matrix.Return the new matrix
	
	Return:SparseMatrix
*/
SparseMatrix SparseMatrix::transpose()
{
	/*	Create rowFlag.The value in rowFlag means
		which row newMatrix.termsArray[index] belongs.

		Example Matrix:
				1 0 0 0
				3 0 0 2
				0 0 5 0
		The termsArray should be:
				[0] 0 0 1
				[1] 1 0 3
				[2] 1 3 2
				[3] 2 2 5
		The rowFalg should be: {0,0,2,3}			
	*/
	int *rowFlag = new int[terms];
	for (int i = 0; i < terms; i++)
	{
		rowFlag[i] = termsArray[i].colume;
	}
	sort(rowFlag, rowFlag + terms);

	//Transpose
	SparseMatrix newMatrix(rows,columns,terms);
	
	for (int index = 0; index < terms; index++)
	{
		//Find the location where termsArray[index] should at in newMatrix 
		int newIndex = -1;
		for (int i = 0; i < terms; i++)
		{
			if (termsArray[index].colume == rowFlag[i])
			{
				newIndex = i;
				break;
			}
		}

		//Exchange row and column
		newMatrix.termsArray[newIndex].row = termsArray[index].colume;
		newMatrix.termsArray[newIndex].colume = termsArray[index].row;
		newMatrix.termsArray[newIndex].value = termsArray[index].value;

		//Mark -1 represents newMatrix.termsArray[newIndex] is unavailable
		rowFlag[newIndex] = -1;
	}
	
	delete[]rowFlag;
	return newMatrix;
}

/*
	Print sparse matrix in format of array.For
	example:
		index  row  column  value
		[0]    1    1       3
		[1]	   2    0       4

	Return:void
*/
void SparseMatrix::prInArray()
{
	cout << "    " << "Index" << "    " << "Row" << "    " << "Column" << "    " << "Value\n";
	for (int i = 0; i < terms; i++)
	{
		cout << "    " << '[' << i << ']'
			<< "    " << termsArray[i].row
			<< "    " << termsArray[i].colume
			<< "    " << termsArray[i].value << '\n';
	}
}

/*
	Print saprse matrix in format of matix.For
	example:
			0  0  1  0
			2  0  0  0
			0  3  0  0

	Return:void
*/
void SparseMatrix::prInMatrix()
{
	int index = 0;
	for (int i = 0; i < rows; i++)
	{
		cout <<'\t';
		for (int j = 0; j < columns; j++)
		{
			if (termsArray[index].row == i && termsArray[index].colume == j)
			{
				cout << termsArray[index].value << '\t';
				index++;
			}
			else
			{
				cout << 0 << '\t';
			}
		}
		cout << endl;
	}
}

/*
	Add a matrix to another.

	Parameter:another	SparseMatrix   The matrix you add to.

	Return:SparseMatrix
*/
SparseMatrix SparseMatrix::add(SparseMatrix &another)
{
	if (rows != another.rows || columns != another.columns)
	{
		cout << "Two matrixs has different dimensions!";
		return SparseMatrix();
	}
	SparseMatrix newMatrix(rows, columns, terms + another.terms);
	int cur_index = 0;
	int ano_index = 0;
	bool goOn = true;
	
	//Add two matrixes
	while (goOn)
	{
		if (termsArray[cur_index]._compare(another.termsArray[ano_index]) > 0)
		{
			newMatrix.addTerm(termsArray[cur_index]);
			cur_index++;
		}
		else if (termsArray[cur_index]._compare(another.termsArray[ano_index]) < 0)
		{
			newMatrix.addTerm(another.termsArray[ano_index]);
			ano_index++;
		}
		else if (termsArray[cur_index]._compare(another.termsArray[ano_index]) == 0)
		{
			int row = termsArray[cur_index].row;
			int col = termsArray[cur_index].colume;
			float value = termsArray[cur_index].value + another.termsArray[ano_index].value;
			newMatrix.addTerm(row, col, value);
			ano_index++;
			cur_index++;
		}

		goOn = cur_index <= finish && ano_index <= another.finish;
	}

	//Add rest terms
	for (; cur_index <= finish; cur_index++)
	{
		newMatrix.addTerm(termsArray[cur_index]);
	}
	for (; ano_index <= another.finish; ano_index++)
	{
		newMatrix.addTerm(another.termsArray[ano_index]);
	}

	return newMatrix;
}

/*
	Minus a matrix by another.

	Parameter:another	SparseMatrix   The matrix you minus by.

	Return:SparseMatrix
*/
SparseMatrix SparseMatrix::minus(SparseMatrix &another)
{
	if (rows != another.rows || columns != another.columns)
	{
		cout << "Two matrixs has different dimensions!";
		return SparseMatrix();
	}
	SparseMatrix newMatrix(rows, columns, terms + another.terms);
	int cur_index = 0;
	int ano_index = 0;
	bool goOn = true;

	//Add two matrixes
	while (goOn)
	{
		if (termsArray[cur_index]._compare(another.termsArray[ano_index]) > 0)
		{
			newMatrix.addTerm(termsArray[cur_index]);
			cur_index++;
		}
		else if (termsArray[cur_index]._compare(another.termsArray[ano_index]) < 0)
		{
			newMatrix.addTerm(-another.termsArray[ano_index]);
			ano_index++;
		}
		else if (termsArray[cur_index]._compare(another.termsArray[ano_index]) == 0)
		{
			int row = termsArray[cur_index].row;
			int col = termsArray[cur_index].colume;
			float value = termsArray[cur_index].value - another.termsArray[ano_index].value;
			newMatrix.addTerm(row, col, value);
			ano_index++;
			cur_index++;
		}

		goOn = cur_index <= finish && ano_index <= another.finish;
	}

	//Add rest terms
	for (; cur_index <= finish; cur_index++)
	{
		newMatrix.addTerm(termsArray[cur_index]);
	}
	for (; ano_index <= another.finish; ano_index++)
	{
		newMatrix.addTerm(another.termsArray[ano_index]);
	}

	return newMatrix;
}

/*
	Matrix multiply by a flaot number

	Parameter:num	float	The float number

	Return:SparseMatrix
*/
SparseMatrix SparseMatrix::multiply(float num)
{
	SparseMatrix newMatrix(rows, columns, terms);
	for (int index = 0; index <= finish; index++)
	{
		int row = termsArray[index].row;
		int col = termsArray[index].colume;
		float value = termsArray[index].value*num;
		newMatrix.addTerm(row, col, value);
	}
	return newMatrix;
}