# SpareMatrix


## Struct:'MatrixTerm'
>class for terms in a matrix 
>
>Memeber variables:
>-
>
>
	int row;
	int colume;
	float value;

>Inner Operations:
>-
> - _compare(MatrixTerm &another): 
> 
> Compare two matrix terms,return1 if current is ahead of another;0 if current is totally equals to another;-1 if current is behind another.

> - operator  '-':
> 
> Invert the term's value.


## class:'SpareMatrix'
>class of a spare matrix

>Memeber varaibles:
>-

>
	MatrixTerm *termsArray;
	int terms;
	int finish;//Point at the finish index of termsArray
	int rows, columns;

>Interfaces:
>-
> - addTerm(int row,int col,int value):

>>Add a  term by given its row , column and value.

>- addTerm(MatrixTerm&term):

>>Add a term by directly given a instance of struct:'MatrixTerm'.

>- prInArray():

>>Print a matrix in format of array,for example

>>
	index  row  column  value
	[0]    1    1       3
	[1]	   2    0       4

>- prInMatrix():

>>Print a matrix in format of row*column matrix,for example

>>
	0  0  1  0
	2  0  0  0
	0  3  0  0

>- transpose():

>>Transpose a matrix and return the transposed matrix.

>- add(SparseMatrix &another):

>>Add a matrix with another.Return he result matrix.

>- minus(SpareMatrix &another):

>>Minus a matrix by another.Return the result matrix.

>- multiply(float num):

>>Multiply a matrix by a number.Return the result matrix.


## TODO:

1. Implement `multiply(SpareMatrix&)` so that it can multiply with anther matrix.
2. Implement `toString()` to simplify output.

10/16/2017 2:57:32 PM 
