#include<iostream>
#include"Matrix.h"

using namespace std;


//================================================================================================
// Matrix class Implimentation
//================================================================================================

//default constructor
matrix::matrix()
{
	row = 1;
	col = 1;
	arr = new double* [row];
	for (int i = 0; i < row; i++)
	{
		arr[i] = new double[col];
	}
	arr[0][0] = 0;
}
//parameterized constructor
matrix::matrix(int row, int col)
{
	//parameters validation
	if (row >= 0 && col >= 0)
	{
		//setting values of rows and columns
		this->row = row;
		this->col = col;
		//creating array for the current constructor
		arr = new double* [row];
		for (int i = 0; i < row; i++)
		{
			arr[i] = new double[col];
		}
		//setting value 0 to the current matrix
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				arr[i][j] = 0;
			}
		}

	}
	else
	{
		cout << "Invalid parameters for constructor...\n";
	}
}
//copy constructor
matrix::matrix(matrix& ref)
{
	this->row = ref.row;
	this->col = ref.col;
	//creating matrix
	arr = new double* [ref.row];
	for (int i = 0; i < ref.row; i++)
	{
		this->arr[i] = new double[ref.col];
	}
	//assigning values
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			this->arr[i][j] = ref.arr[i][j];
		}
	}
}

void matrix::resize(int row, int col)
{
	//creating new matrix
	//parameters validation
	if (row >= 0 && col >= 0)
	{
		//creating array for the current constructor
		double** arrNew = new double* [row];
		for (int i = 0; i < row; i++)
		{
			arrNew[i] = new double[col];
		}
		//assigning values
		for (int i = 0; i < this->row; i++)
		{
			for (int j = 0; j < this->col; j++)
			{
				arrNew[i][j] = this->arr[i][j];
			}
		}

		//deleting old matrix
		for (int i = 0; i < this->row; i++)
		{
			delete[] arr[i];
		}
		delete[] arr;


		this->arr = arrNew;
		//setting values of rows and columns
		this->row = row;
		this->col = col;
		//arrNew = nullptr;

	}


}

//setter
void matrix::setValue(double value, int row, int col)
{
	if (row <= this->row && col <= this->col)
	{
		if (row > 0 && col > 0)
		{
			this->arr[row - 1][col - 1] = value;
		}
	}
}

//getter
double matrix::getValue(int row, int col)
{
	if (row <= this->row && col <= this->col)
	{
		if (row > 0 && col > 0)
		{
			return this->arr[row - 1][col - 1];
		}
	}
	return 0;
}


//Chacks identity
bool matrix::isIdentity()
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; i++)
		{
			if (i == j && arr[i][j] != 1)
			{
				return false;
			}
			else
			{
				if (i != j && arr[i][j] != 0)
				{
					return false;
				}
			}
		}
	}
	return true;
}


//checks, lower triangle
bool matrix::isLowerTriangular()
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; i++)
		{
			if (i < j && arr[i][j] != 0)
				return false;
		}
	}

	return true;
}

//checks, upper triangle
bool matrix::isUpperTriangular()
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; i++)
		{
			if (i > j && arr[i][j] != 0)
				return false;
		}
	}
	return true;
}


//checks tri-anglular
bool matrix::isTriangular()
{
	if (isUpperTriangular())
	{
		return true;
	}
	if (isLowerTriangular())
	{
		return true;
	}

	return false;
}

//checks if matrix are erual or not.
bool matrix::isEqual(matrix& ref)
{
	//checking if dimentions are not same
	if (this->row != ref.row || this->col != ref.col)
	{
		return false;
	}

	//checking for every element of the matrix
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (arr[i][j] != ref.arr[i][j])
			{
				return false;
			}
		}
	}
	//return true if all conditions are OK!!!
	return true;
}

//taking transpose of the matrix
matrix matrix::transpose()
{
	//creating new matrix
	matrix tran(this->col, this->row);

	//assigning values to the new matrix (transposed dimentions)
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			tran.arr[j][i] = this->arr[i][j];
		}
	}

	return tran;
}

//adding two matrices
matrix matrix::add(const matrix& ref)
{
	//creating new matrix
	matrix result(this->row, this->col);

	if (this->row != ref.row || this->col != ref.col)
	{
		cout << "ERROR!!! Not compatible for addition...\n";
		return result;
	}

	//assigning values to the new matrix
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			result.arr[i][j] = this->arr[i][j] + ref.arr[i][j];
		}
	}

	return result;
}

//adding two matrices
matrix matrix::subtract(matrix& ref)
{
	//creating new matrix
	matrix result(this->row, this->col);

	if (this->row != ref.row || this->col != ref.col)
	{
		cout << "ERROR!!! Not compatible for subtraction...\n";
		return result;
	}

	//assigning values to the new matrix
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			result.arr[i][j] = this->arr[i][j] - ref.arr[i][j];
		}
	}

	return result;
}

//dividing the matrix by a scaler number
matrix matrix::divide(double num)
{
	//creating new matrix
	matrix div(this->row, this->col);

	//assigning values to the new matrix (transposed dimentions)
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			div.arr[i][j] = (this->arr[i][j] / num);
		}
	}

	return div;
}

//multiplies two 2-D arr 
matrix matrix::multiply(const matrix& ref)
{
	//creates new matrix, to store product of two arrays
	matrix prod(row, ref.col);

	if (this->col != ref.row)
	{
		cout << "ERROR!!! Not compatible for multiplications...\n";
		return prod;
	}

	//multiplying matrices
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < ref.col; j++)
		{
			for (int k = 0; k < col; k++)
			{
				prod.arr[i][j] += this->arr[i][k] * ref.arr[k][j];
			}
		}
	}

	return prod;
}

matrix matrix::operator=(const matrix& ref)
{
	resize(ref.row, ref.col);

	this->row = ref.row;
	this->col = ref.col;

	//setting values to the current matrix
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			arr[i][j] = ref.arr[i][j];
		}
	}

	return *this;

}

//checks if matrix is symmetry...
bool matrix::isSymmetric()
{
	matrix tran(this->col, this->row);
	tran = transpose();
	//compares the transpose, to check symmetric
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (tran.arr[i][j] != arr[i][j])
				return false;
		}
	}
	return true;
}

bool matrix::isSkewSymmetric()
{
	matrix tran(this->col, this->row);
	tran = transpose();
	//compares the transpose, to check skew-symmetric
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (tran.arr[i][j] != (-1 * arr[i][j]))
				return false;
		}
	}
	return true;
}

//input
void matrix::input()
{
	cout << endl;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << "Row " << i + 1 << " Column " << j + 1 << " : ";
			cin >> arr[i][j];
		}
	}
}

//Displays the matrix
void matrix::display()
{
	cout << endl;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			cout << arr[i][j] << "  ";

		cout << endl;
	}
}


matrix::~matrix()
{
	for (int i = 0; i < row; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;
}

void matrix::RunObject()
{
	cout << "\n=================================================================================================== \n";
	cout << "*                                Matrix                                                           * ";
	cout << "\n=================================================================================================== \n\n";
	int row, col;
	cout << "Enter number of rows a matric A: ";
	cin >> row;
	while (row < 1)
	{
		cout << "Please enter a valid number: ";
		cin >> row;
	}
	cout << "Enter number of columns a matric A: ";
	cin >> col;
	while (col < 1)
	{
		cout << "Please enter a valid number: ";
		cin >> col;
	}

	matrix A(row, col);
	cout << "Enter the elements of the matrix: \n";
	A.input();
	cout << "\n=================================================================================================== \n\n";
	cout << " Properties \n\n";

	int count = 1;
	if (A.isIdentity())
	{
		cout << count << ". Identity matrix \n";
		count++;
	}

	if (A.isTriangular())
	{
		cout << count << ". Triangular matrix \n";
		count++;
	}

	if (A.isLowerTriangular())
	{
		cout << count << ". Lower triangular matrix\n";
		count++;
	}

	if (A.isUpperTriangular())
	{
		cout << count << ". Upper triangular matrix \n";
		count++;
	}

	if (A.isSymmetric())
	{
		cout << count << ". Symmetric matrix \n";
		count++;
	}

	if (A.isSkewSymmetric())
	{
		cout << count << ". Skew Symmetric matrix \n";
		count++;
	}

	cout << "\n\n Please selelct the Operation\n\n";
	cout << "1. Add Matrices \n";
	cout << "2. Subtract Matrices \n";
	cout << "3. Multiplay Matrices \n";
	cout << "4. Division by a scaler number \n";
	cout << "5. Transpose of a Matrix \n";
	cout << "6. Exit \n";

	string input;
	char ch;
	cin.ignore();
	cin >> input;
	ch = input[0];

	if (ch >= '1' && ch <= '3')
	{
		cout << "Enter number of rows a matric B: ";
		cin >> row;
		while (row < 1)
		{
			cout << "Please enter a valid number: ";
			cin >> row;
		}
		cout << "Enter number of columns a matric B: ";
		cin >> col;
		while (col < 1)
		{
			cout << "Please enter a valid number: ";
			cin >> col;
		}

		matrix B(row, col);
		cout << "Enter the elements of the matrix: \n";
		B.input();
		cout << "\n=================================================================================================== \n\n";
		cout << "Matrix A:    ";
		A.display();

		cout << "\nMatrix B:    ";
		B.display();
		cout << "\n\n";
		matrix C;

		if (ch == '1')
		{
			C = A.add(B);
			cout << "A + B ";
			C.display();
		}
		if (ch == '2')
		{
			C = A.subtract(B);
			cout << "A - B ";
			C.display();
		}
		if (ch == '3')
		{
			C = A.multiply(B);
			cout << "A * B ";
			C.display();
		}
	}

	matrix D;
	if (ch == '4')
	{
		double num;
		cout << "Enter the number to divide \n";
		cin >> num;
		while (num == 0)
		{
			cout << "Division By 0 is not possible \n Enter again: ";
			cin >> num;
		}
		D = A.divide(num);
		cout << "\n Division of A by " << num << endl;
		D.display();

	}
	if (ch == '5')
	{
		D = A.transpose();
		cout << "\n Transpose of A ";
		D.display();
	}

	cout << "\n=================================================================================================== \n\n";
	if (ch != '6')
	{
		system("pause");
	}
}






//int main()
//{
//	matrix M;
//	M.RunObject();
//	return 0;
//}
