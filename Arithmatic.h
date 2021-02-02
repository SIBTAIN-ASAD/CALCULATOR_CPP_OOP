#pragma once
#include<iostream>
#include<string>
#include<sstream>
#include"BigInt.h"
#include"Calculator.h"
using namespace std;

//================================================================================================
// Arithmatic class header
//================================================================================================

class Arithmatic : public Calculator
{
private:
	string input;
	BigInt* dataLeft;
	BigInt* dataRight;

public:
	Arithmatic();
	bool isOperator(char ch);
	bool isNumber(char ch);
	bool isValid();
	int NoOfOperators();
	int findOperator();
	int findPreviousOperator(int position);
	int findNextOperator(int position);
	void StringManuplate();
	void RunObject();
	~Arithmatic();
};



