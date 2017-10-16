//main.cpp : Main function to test class:'SparseMatrix'
#include "SparseMatrix.h"
#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
	SparseMatrix matrix1(3, 3, 5);
	matrix1.addTerm(0, 0, 2);
	matrix1.addTerm(1, 0, 3);
	matrix1.addTerm(1, 2, 3);
	matrix1.addTerm(2, 1, 4);
	matrix1.addTerm(2, 2, 5);
	SparseMatrix matrix2(3, 3, 1);
	matrix2.addTerm(1, 1, 7);

	//Test print
	cout << "Matrix1:\n";
	matrix1.prInMatrix();
	cout << "\nMatrix2:\n";
	matrix2.prInMatrix();

	//Test add
	SparseMatrix matrix3 = matrix1.add(matrix2);
	cout << "\nMatrix1 + Matrix2:\n";
	matrix3.prInMatrix();

	//Test minus
	SparseMatrix matrix4 = matrix1.minus(matrix2);
	cout << "\nMatrix1 - Matrix2:\n";
	matrix4.prInMatrix();

	//Test multiply by a float number
	SparseMatrix matrix5 = matrix1.multiply(2.5);
	cout << "\nMatrix * 2.5:\n";
	matrix5.prInMatrix();

	//Test transpose
	SparseMatrix temp = matrix1.transpose();
	cout << "\nMatrix1 after transpose :\n";
	temp.prInMatrix();

	system("pause");
	return 0;
}