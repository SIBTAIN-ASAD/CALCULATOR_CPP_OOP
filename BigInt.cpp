#include<iostream>
#include<string>
#include<sstream>
#include"BigInt.h"
using namespace std;



//================================================================================================
// BigInt class Implimentation
//================================================================================================


//default constructor
BigInt::BigInt()
{
	data = new string("0");
	intPart = new string("0");
	dblPart = 0;
	lengthOffloat = 0;
}


//copy constructor
BigInt::BigInt(BigInt& ref)
{
	this->data = new string;
	*data = *(ref.data);
	this->intPart = new string;
	*intPart = *(ref.intPart);

	this->dblPart = ref.dblPart;
	this->lengthOffloat = ref.lengthOffloat;
}


//parameterized constructor
BigInt::BigInt(char* input, int length)
{
	data = new string(input, length);

	//seperating intiger part of the string
	int n = length;
	//loops returns the position of (.) in the string

	for (int i = 0; i < length; i++)
	{
		if ((*data)[i] == '.')
		{
			n = i;
		}
	}
	if (n == 0)
	{
		intPart = new string("0", 1);
	}
	else
	{
		intPart = new string(input, n);
	}

	//calculating the length of floating number
	int count = 0;
	for (int i = 0; i < length; i++)
	{
		lengthOffloat++;
		if ((*data)[i] == '.')
		{
			count++;
			lengthOffloat = 0;
		}
	}
	if (count == 0)
	{
		lengthOffloat = 0;
	}



	//seperating floating part of the number part
	int divisor = 10;
	dblPart = 0.0;

	for (int i = n + 1; i < length; i++)
	{
		if ((*data)[i] >= '0' && ((*data)[i] <= '9'))
		{
			dblPart = dblPart + ((static_cast<double>((*data)[i]) - 48) / divisor);
			divisor *= 10;
		}
	}

}


//convet a string value to double
double BigInt::toDbl()
{
	double num = 0;
	int count = 0;
	double flag = 1; //to reset value of num at dot
	bool flag_1 = false; //to reset value at only first dot
	for (unsigned int i = 0; i < data->length(); i++)
	{
		if ((*data)[i] == '.' && flag_1 == false)
		{
			flag = 1;
			flag_1 = true;
			count++;
		}
		if ((*data)[i] >= '0' && ((*data)[i] <= '9'))
		{
			num = num * 10 + ((*data)[i] - 48);
			flag *= 10;
		}
	}
	if (count > 0)
		num = num / flag;

	return num;
}



// conversion from given Double in parameter to String (use as it is)
string BigInt::convert(double a)
{
	ostringstream oss;
	oss << a;
	return oss.str();
}



//this function tell weather the given part is bigger or not
bool BigInt::isGreater(BigInt left)
{
	//checking int part
	for (unsigned int i = 0; i < this->intPart->length(); i++)
	{
		if ((*intPart)[i] > (*(left.intPart))[i])
		{
			return true;
		}
		if ((*intPart)[i] < (*(left.intPart))[i])
		{
			return false;
		}
	}
	//checking double part
	if (this->dblPart < left.dblPart)
	{
		return false;
	}
	else
	{
		return true;
	}
}




//addition of two numbers
string BigInt::add(BigInt left)
{
	int length = 0;

	/* Equating the lengths of both numbers by inserting "0"s at start to do fine addition*/
	if (this->intPart->length() < left.intPart->length())
	{
		while (this->intPart->length() < left.intPart->length())
		{
			this->intPart->insert(0, "0");
		}
		length = intPart->length();
	}
	else
	{

		while (this->intPart->length() > left.intPart->length())
		{
			left.intPart->insert(0, "0");
		}
		length = left.intPart->length();
	}


	//array to store the result of addition (as result could increase by se 1 so it have additional 1 size) 
	char* result = new char[length + 1];
	result[0] = '0';
	int carry = 0;

	//adding the double part
	double sumDbl = this->dblPart + left.dblPart;
	//if sum is greater then zero . it would reduce it by 1 and send a carry as per maths rules
	if (sumDbl >= 1)
	{
		sumDbl = sumDbl - 1;
		carry = 1;
	}

	//vaaraible to store the result
	char sum = '0';

	//addition of numbers one by one
	for (int i = length - 1; i >= 0; i--)
	{
		sum = (*intPart)[i] + (*(left.intPart))[i];

		//by calculating ascii we have to reduce it by 48 
		sum = sum - 48;
		sum += carry;
		if (sum > 57)
		{
			carry = 1;
			sum -= 10;
		}
		else
		{
			carry = 0;
		}

		result[i + 1] = sum;
	}
	if (carry == 1)
	{
		result[0] = '1';
	}


	//converting double to string
	string addDbl = this->convert(sumDbl);
	//as double have a zero at start to we have to remove it
	addDbl.erase(0, 1);
	//converting resultant array to string
	string addInt(result, length + 1);

	string finalStr;
	if (sumDbl > 0)
	{
		finalStr = addInt + addDbl;
	}
	else
	{
		finalStr = addInt;
	}

	//removing irrevant zeroes at start
	while (finalStr[0] == '0')
	{
		finalStr.erase(0, 1);
	}

	//releasing memory
	delete[] result;
	//returning string
	return finalStr;
}

string BigInt::subtract(BigInt left)
{
	int length = 0;
	if (this->intPart->length() < left.intPart->length())
	{
		while (this->intPart->length() < left.intPart->length())
		{
			this->intPart->insert(0, "0");
		}
		length = intPart->length();
	}
	else
	{
		while (this->intPart->length() > left.intPart->length())
		{
			left.intPart->insert(0, "0");
		}
		length = left.intPart->length();
	}



	char* result = new char[length + 1];
	int borrow = 0;
	double subDbl = 0;
	char sub = '0';

	if (isGreater(left))
	{
		result[0] = '+';
		subDbl = this->dblPart - left.dblPart;
		if (subDbl < 0)
		{
			subDbl = subDbl + 1;
			borrow = 1;
		}

		for (int i = length - 1; i >= 0; i--)
		{
			sub = (*intPart)[i] - (*(left.intPart))[i] + 48;
			sub = sub - borrow;
			if (sub < 48)
			{
				borrow = 1;
				sub += 10;
			}
			else
			{
				borrow = 0;
			}

			result[i + 1] = sub;
		}
	}
	else
	{
		result[0] = '-';
		subDbl = left.dblPart - this->dblPart;
		if (subDbl < 0)
		{
			subDbl = subDbl + 1;
			borrow = 1;
		}


		sub = '0';

		for (int i = length - 1; i >= 0; i--)
		{
			sub = (*(left.intPart))[i] - (*intPart)[i] + 48;
			sub -= borrow;
			if (sub < 48)
			{
				borrow = 1;
				sub += 10;
			}
			else
			{
				borrow = 0;
			}

			result[i + 1] = sub;
		}

	}


	string ResultDbl = this->convert(subDbl);
	ResultDbl.erase(0, 1);
	string subInt(result, length + 1);

	string finalStr = subInt;

	if (subDbl != 0)
	{
		finalStr = subInt + ResultDbl;
	}

	while (finalStr[1] == '0')
	{
		finalStr.erase(0, 1);
	}


	//releasing memory
	delete[] result;
	//returning string
	return finalStr;
}


//getting string with just numbers
string BigInt::getPureString()
{
	string str = *(this->data);
	for (unsigned int i = 0; i < (this->data->length()); i++)
	{
		if (str[i] < '0' || str[i] > '9')
		{
			str.erase(i, 1);
		}
	}

	return str;
}



//addition of two pure strings (containg just numbers) and return there sum
string BigInt::addStrings(string left, string right)
{
	int length = 0;
	if (right.length() < left.length())
	{
		while (right.length() < left.length())
		{
			right.insert(0, "0");
		}
		length = right.length();
	}
	else
	{

		while (right.length() > left.length())
		{
			left.insert(0, "0");
		}
		length = left.length();
	}

	char* result = new char[length + 1];
	result[0] = '0';
	int carry = 0;

	char sum = '0';

	for (int i = length - 1; i >= 0; i--)
	{
		sum = left[i] + right[i];
		sum = sum - 48;
		sum += carry;
		if (sum > 57)
		{
			carry = 1;
			sum -= 10;
		}
		else
		{
			carry = 0;
		}

		result[i + 1] = sum;
	}
	if (carry == 1)
	{
		result[0] = '1';
	}


	string finalStr(result, length + 1);

	//releasing memory
	delete[] result;
	//returning string
	return finalStr;
}



string BigInt::multiply(BigInt left)
{
	string rightStr = this->getPureString();
	string leftStr = left.getPureString();

	string total("0");
	string grandTotal("0");
	string zeroes("0");

	//loop to add resultant numbers as:
	/*
	*		234.6
	*		876.2
	*		-----
	*		4692 <---to add these numbers
	*	  14078X <----'
	*	 16402XX
	*/
	for (int j = leftStr.length() - 1; j >= 0; j--)
	{
		int num = static_cast<int>((leftStr[j]) - 48);
		total = "0";

		//loop add the first with itself :times equal to respected digit of 2nd number
		for (int i = 0; i < num; i++)
		{
			total = addStrings(total, rightStr);
		}
		//total of all the nubmers
		grandTotal = addStrings((total + zeroes), grandTotal);
		zeroes = zeroes + "0";
	}

	//check if there is not any number in the grand total
	if (grandTotal.length() > 0)
	{
		//inserting the dot(.) at valid point
		int value = (this->lengthOffloat + left.lengthOffloat);
		int index = grandTotal.length() - value;
		grandTotal.insert(index - 1, ".");
		while (grandTotal[0] == '0')
		{
			grandTotal.erase(0, 1);
		}
	}
	else
	{
		grandTotal = "0";
	}


	return grandTotal;

}

//dividing the two BigInts 
/* Not done for larger numbers as already asked From TA to not to do this */
string BigInt::divide(BigInt left)
{
	double a = this->toDbl();
	double b = left.toDbl();

	if (b == 0)
	{
		string error("## Math Error ##");
		return error;
	}
	double c = a / b;
	string result = this->convert(c);

	return result;
}


//destructor
BigInt::~BigInt()
{
	delete data;
	delete intPart;
}




