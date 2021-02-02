#pragma once
#include<iostream>
#include"calculator.h"
using namespace std;


//================================================================================================
// Matrix class Header
//================================================================================================


class matrix : public Calculator
{
private:
	double** arr;
	int row;
	int col;

public:
	matrix();
	matrix(int, int);
	matrix(matrix& ref);
	void resize(int row, int col);
	void setValue(double value, int row, int col);
	double getValue(int row, int col);
	bool isIdentity();
	bool isLowerTriangular();
	bool isUpperTriangular();
	bool isTriangular();
	bool isEqual(matrix& ref);
	matrix transpose();
	matrix add(const matrix& ref);
	matrix subtract(matrix& ref);
	matrix divide(double num);
	matrix multiply(const matrix& ref);
	matrix operator=(const matrix& ref);
	bool isSymmetric();
	bool isSkewSymmetric();
	void input();
	void display();
	~matrix();
	void RunObject();
};

