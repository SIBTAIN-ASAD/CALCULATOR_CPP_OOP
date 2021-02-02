#include<iostream>
#include<string>
#include<sstream>
#include<cstdlib>
#include"BigInt.h"
#include"Arithmatic.h"
using namespace std;



//================================================================================================
// Arithmatic class Implimentation
//================================================================================================


//deafult constructor
Arithmatic::Arithmatic()
{
	dataLeft = new BigInt;
	dataRight = new BigInt;
}

//this function is used to check weither the given character is an operator or not
bool Arithmatic::isOperator(char ch)
{
	if (ch == '/' || ch == '*' || ch == '+' || ch == '-')
	{
		return true;
	}
	else
	{
		return false;
	}
}

//this function is used to check weither the given character is a number or not
bool Arithmatic::isNumber(char ch)
{
	if (ch >= '0' && ch <= '9')
	{
		return true;
	}
	else
	{
		return false;
	}
}




//this function is used to check weither the given expression is valid or not
/* expression is invalid if it contains other than operators and numbers */
/* expression is invalid if it two operators are entered simultaniously */
/* expression is invalid if it have a dot (.) just after an operator */
/* expression is invalid if it two dots (.) are entered simultaniously */
bool Arithmatic::isValid()
{
	//check that user should not enter any invalid character 
	for (unsigned int i = 0; i < input.length(); i++)
	{
		if ((!isOperator(input.at(i))) && (!isNumber(input.at(i))) && input.at(i) != '.')
		{
			return false;
		}
	}

	//check for invalid arrangement of operators
	for (unsigned int i = 0; i < (input.length() - 1); i++)
	{
		//check that user should not enter two operators simulataniously
		if ((isOperator(input.at(i))) && (isOperator(input.at(i + 1))))
		{
			return false;
		}
		//check that user should not enter operator just after a dot
		if ((input.at(i) == '.') && (isOperator(input.at(i + 1))))
		{
			return false;
		}
		//check that user should not enter two dots simulataniously
		if ((input.at(i) == '.') && (input.at(i + 1) == '.'))
		{
			return false;
		}
	}

	//check that user should not enter an operator at the start or at the end of the string
	if ((input.at(0) == '/') || (input.at(0) == '*') || isOperator(input.at(input.length() - 1)))
	{
		return false;
	}

	//check that user should not enter a dot at the end of the string
	if (input.at(input.length() - 1) == '.')
	{
		return false;
	}

	return true;

}

//this function is used to count the number of operators
int Arithmatic::NoOfOperators()
{
	int count = 0;
	for (unsigned int i = 1; i < input.length(); i++)
	{
		if (isOperator(input.at(i)))
		{
			count++;
		}
	}
	return count;
}


//this function retrun the position of most wanted operator in string according to DMAS rule
int Arithmatic::findOperator()
{
	//finding / operator
	for (unsigned int i = 1; i < input.length(); i++)
	{
		if (input[i] == '/')
		{
			return i;
		}
	}
	//finding * operator
	for (unsigned int i = 1; i < input.length(); i++)
	{
		if (input[i] == '*')
		{
			return i;
		}
	}
	//finding + operator
	for (unsigned int i = 1; i < input.length(); i++)
	{
		if (input[i] == '+')
		{
			return i;
		}
	}
	//finding - operator
	for (unsigned int i = 1; i < input.length(); i++)
	{
		if (input[i] == '-')
		{
			return i;
		}
	}

	return -1;

}

//this function return the position of previous operator
//if not any operator found ... it return -1
int Arithmatic::findPreviousOperator(int position)
{
	int previous = position - 1;
	while (previous >= 0)
	{
		if (isOperator(input[previous]))
		{
			return previous;
		}
		previous--;
	}

	return -1;
}

//this function return the position of next operator
// if not any operator found ... it returns length of the input string
int Arithmatic::findNextOperator(int position)
{
	for (unsigned int i = position + 1; i < (this->input.length()); i++)
	{
		if (isOperator(input[i]))
		{
			return i;
		}
	}

	return input.length();
}



//this function is used to manuplate the string of valid input expression
void Arithmatic::StringManuplate()
{
	char* left;
	char* right;


	//getting position of the operator in the input string according to DMAS rules
	const int position = findOperator();

	//=============================
	//getting values in left array
	//=============================

	//getting the position of previous character, thus starting point of left sided number
	int start = findPreviousOperator(position) + 1;
	int Llength = position - start;
	//populating left char array
	left = new char[Llength];
	for (int i = 0; i < Llength; i++)
	{
		left[i] = input[start];
		start++;
	}

	//=============================
	//getting values in right array
	//=============================

	//getting the position of previous character, thus starting point of left sided number
	int end = findNextOperator(position);
	start = position + 1;
	int Rlength = end - start;
	//populating right char array
	right = new char[Rlength];
	for (int i = 0; i < Rlength; i++)
	{
		right[i] = input[start];
		start++;
	}

	//=================================================================
	// performing operation
	//=================================================================
	delete dataLeft;
	delete dataRight;
	dataLeft = new BigInt(left, Llength);
	dataRight = new BigInt(right, Rlength);


	string result;
	int pre = findPreviousOperator(position);
	//division case
	if (input[position] == '/')
	{
		result = dataLeft->divide(*dataRight);
		//this nested if else adjust the previous sign of the result after calculations
		if (pre >= 0 && input[pre] == '*')
		{
			result.insert(0, "*");
		}
		else
		{
			if (pre >= 0 && input[pre] == '+')
			{
				result.insert(0, "+");
			}
			else
			{
				if (pre >= 0 && input[pre] == '-')
				{
					result.insert(0, "-");
				}
				else
				{
					result.insert(0, "+");
				}
			}
		}

	}
	//multiplication case
	if (input[position] == '*')
	{
		result = dataLeft->multiply(*dataRight);
		//this nested if else adjust the previous sign of the result after calculations
		if (pre >= 0 && input[pre] == '+')
		{
			result.insert(0, "+");
		}
		else
		{
			if (pre >= 0 && input[pre] == '-')
			{
				result.insert(0, "-");
			}
			else
			{
				result.insert(0, "+");
			}
		}
	}
	//addition case
	if (input[position] == '+')
	{
		//this nested if else see the previous sign and do the operation accordingly
		if (pre >= 0 && input[pre] == '+')
		{
			result = dataLeft->add(*dataRight);
			result.insert(0, "+");
		}
		else
		{
			if (pre >= 0 && input[pre] == '-')
			{
				result = dataRight->subtract(*dataLeft);
			}
			else
			{
				result = dataLeft->add(*dataRight);
				result.insert(0, "+");
			}
		}
	}
	//subtraction case
	if (input[position] == '-')
	{
		if (pre >= 0 && input[pre] == '-')
		{
			result = dataLeft->add(*dataRight);
			result.insert(0, "-");
		}
		else
		{
			result = dataLeft->subtract(*dataRight);
		}
	}

	//=================================================================
	// removing and inserting data in the string
	//=================================================================
	start = findPreviousOperator(position);
	if (start == -1)
	{
		start = 0;
	}
	end = findNextOperator(position);
	int size = end - start;

	input.erase(start, size);
	input.insert(start, result);

	delete[] left;
	delete[] right;
}


//virtual function of class to run the object
void Arithmatic::RunObject()
{
	cout << "\n=================================================================================================== \n";
	cout << "*                                Arithmatic                                                       * ";
	cout << "\n=================================================================================================== \n\n";
	cout << "                          Please enter the Arithmatic expression                                      \n";
	getline(cin, this->input);

	//input validation
	while (!(isValid()))
	{
		cout << "Invalid Expression...\n Try Again \n";
		getline(cin, this->input);
	}

	//StringManuplate();
	int numOp = NoOfOperators();
	bool check = true;
	for (int i = 0; i < numOp; i++)
	{
		//divide by zero error
		for (int i = 0; i < input.length(); i++)
		{
			if (input[i] == '#')
			{
				this->input = "Math Error...";
				check = false;
			}
		}
		if (check == false)
		{
			break;
		}


		StringManuplate();
	}
	cout << endl << "Answer ... \n";
	//displaying result
	cout << this->input << endl;

	cout << "\n=================================================================================================== \n\n";

	system("pause");
}

//destructor
Arithmatic::~Arithmatic()
{
	delete dataLeft;
	delete dataRight;
}


//int main()
//{
//	Arithmatic A;
//	A.RunObject();
//
//	return 0;
//}
