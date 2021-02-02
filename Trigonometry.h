#pragma once
#include<iostream>
#include<string>
#include"Calculator.h"
using namespace std;


//================================================================================================
// Trigonometry class Header
//================================================================================================

class trigonometry : public Calculator
{
private:
    double angle;
public:
    trigonometry();
    trigonometry(double num);
    double getSin();
    double getCosin();
    double getTangent();
    double getSecant();
    double getCosecant();
    double getCotangent();
    void RunObject();
};