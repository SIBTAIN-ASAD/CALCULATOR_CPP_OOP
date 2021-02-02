#pragma once
#include<iostream>
#include"Calculator.h"
using namespace std;


//================================================================================================
// Fraction class Header
//================================================================================================

class MixedFraction : public Calculator
{
private:
    int integer;     // Integral part of the Mixed fraction. 
    int numerator;   // Numerator of the fractional part. 
    int denominator; // Denominator of the fractional part. This must be non-zero 
public:
    MixedFraction(); // Initialize data members to default values. Remember denominator must not be zero. 
    MixedFraction(int a_integer, int a_nmrator, int a_dnmnator); // Initialize data members with parameter values. 
                                                                  //A mixed number can be negative or positive. 
                                                                  //If the mixed number is to be negative, only integer part can be negative, not numerator or denominator. 
    MixedFraction(int a_integer);                        // Constructor with only integer part, set fractional part to zero.
    MixedFraction(const MixedFraction& a_mFrac);         // copy constructor.
    ~MixedFraction();                                   // Destructor should display message “Object is destroyed”. 
    void setIntegralPart(int a_intgr);                    //setter intiger value
    bool setDenominator(int a_dnmnator);                  //setter denominator
    void setNumerator(int a_nmrator);                     //setter numerator
    int getIntegralPart() const;                         //getter intiger
    int getDenominator() const;                          //getter denominator
    int getNumerator()const;                             //getter numerator
    double evaluate();                                    // should return the decimal equivalent of the mixed number. 
    void display();                                       // should display the fraction in proper format i.e. 3 2/5.
    void RunObject();
    MixedFraction operator+(const MixedFraction&); // overload binary + operator. 
    MixedFraction operator-(const MixedFraction&); // overload binary – operator. 
    MixedFraction operator*(const MixedFraction&); // overload binary * operator. 
    MixedFraction operator/(const MixedFraction&); // overload binary / operator.
    bool operator==(MixedFraction&);               // overload relational == operator
    bool operator<(MixedFraction&);                // overload relational != operator.
    MixedFraction operator-();                      // overload unary – operator.
    MixedFraction operator++();                     // overload pre-increment operator.
    MixedFraction operator++(int);                  // overload post-increment operator.
    MixedFraction operator+=(const MixedFraction&);// overload combined operator +=
    MixedFraction operator/=(const MixedFraction&);// overload combined operator /=
    MixedFraction operator=(const MixedFraction&);  //overloading equal operator
};
