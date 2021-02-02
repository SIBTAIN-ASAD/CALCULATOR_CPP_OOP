#pragma once
#include<iostream>
#include<string>
#include<sstream>
using namespace std;

//================================================================================================
// BigInt class Header
//================================================================================================
class BigInt
{
private:
	string* data;
	double dblPart;
	string* intPart;
	int lengthOffloat;
public:
	BigInt();
	BigInt(BigInt& ref);
	BigInt(char* input, int length);
	double toDbl();
	string convert(double a);
	bool isGreater(BigInt left);
	string add(BigInt left);
	string subtract(BigInt left);
	string getPureString();
	string addStrings(string left, string right);
	string multiply(BigInt left);
	string divide(BigInt left);
	~BigInt();
};

