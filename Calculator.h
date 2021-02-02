#pragma once
#include<iostream>
#include<string>

using namespace std;

class Calculator
{
public:
	virtual void RunObject() = 0;
	virtual ~Calculator();
};
