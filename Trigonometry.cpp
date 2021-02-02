#include<iostream>
#include<string>
#include<cstdlib>
#include"Trigonometry.h"
using namespace std;

//================================================================================================
// Trigonometry class Implimentation
//================================================================================================


trigonometry::trigonometry()
{
    angle = 0;
}
trigonometry::trigonometry(double num)
{
    angle = num;
}

//function to calculate the sin value
double trigonometry::getSin()
{
    double x = this->angle;
    int check = static_cast<int>(x);
    double check2 = x - check;

    if ((check2 == 0) && (((check % 360) == 0) || (check % 360) == 180))
    {
        return 0.0;
    }


    x = (x * (355.00 / 113.00)) / 180;
    int n = 100;
    double value1, value2, less, old, prod, fac, result, result1;
    double value = 3;
    //sum of negative terms of series
    double total_negative = 0;
    while (value <= n)
    {
        value1 = value;
        value2 = value;
        less = value - 1;
        old = x;

        while (value1 > 1)
        {
            prod = old * x;
            old = prod;
            value1 = value1 - 1;
        }

        while (less > 1)
        {
            fac = value2 * less;
            value2 = fac;
            less = less - 1;
        }

        result = prod / fac;
        result1 = result + total_negative;
        total_negative = result1;
        value = value + 4;
    }

    double total_positive = 0;
    value = 5;
    //sum of positive terms of series

    while (value <= n)
    {
        value1 = value;
        value2 = value;
        less = value - 1;
        old = x;

        while (value1 > 1)
        {
            prod = old * x;
            old = prod;
            value1 = value1 - 1;
        }


        while (less > 1)
        {
            fac = value2 * less;
            value2 = fac;
            less = less - 1;
        }

        result = prod / fac;
        result1 = result + total_positive;
        total_positive = result1;
        value = value + 4;

    }

    double sinx = x + total_positive - total_negative;

    return sinx;
}



//funnction to calculate the cos value
double trigonometry::getCosin()
{
    double x = this->angle;
    int check = static_cast<int>(x);
    double check2 = x - check;

    if ((check2 == 0) && (((check % 360) == 90) || (check % 360) == 270))
    {
        return 0.0;
    }

    x = (x * (355.00 / 113.00)) / 180;
    int n = 50;
    double value1, value2, less, old, prod, fac, result, result1;
    double value = 2;
    //sum of negative terms of series
    double total_negative = 0;
    while (value < n)
    {
        value1 = value;
        value2 = value;
        less = value - 1;
        old = x;

        while (value1 > 1)
        {
            prod = old * x;
            old = prod;
            value1 = value1 - 1;
        }

        while (less >= 1)
        {
            fac = value2 * less;
            value2 = fac;
            less = less - 1;
        }

        result = prod / fac;
        result1 = result + total_negative;
        total_negative = result1;
        value = value + 4;
    }

    double total_positive = 0;
    value = 4;
    //sum of positive terms of series

    while (value < n)
    {
        value1 = value;
        value2 = value;
        less = value - 1;
        old = x;

        while (value1 > 1)
        {
            prod = old * x;
            old = prod;
            value1 = value1 - 1;
        }


        while (less >= 1)
        {
            fac = value2 * less;
            value2 = fac;
            less = less - 1;
        }

        result = prod / fac;
        result1 = result + total_positive;
        total_positive = result1;
        value = value + 4;

    }

    double cosx = 1 + total_positive - total_negative;

    return cosx;
}


//funnction to calculate the tan value
double trigonometry::getTangent()
{
    double sinx = getSin();
    double cosx = getCosin();
    if (cosx == 0)
    {
        cout << "Infinty \n";
        return 0;
    }
    return (sinx / cosx);

}

//funnction to calculate the secant value
double trigonometry::getSecant()
{
    double cosx = getCosin();
    if (cosx == 0)
    {
        cout << "Infinty \n";
        return 0;
    }
    return (1 / cosx);
}

//funnction to calculate the cosecant value
double trigonometry::getCosecant()
{
    double sinx = getSin();
    if (sinx == 0)
    {
        cout << "Infinty \n";
        return 0;
    }
    return (1 / sinx);
}


//funnction to calculate the Coatangent value
double trigonometry::getCotangent()
{
    double sinx = getSin();
    double cosx = getCosin();
    if (sinx == 0)
    {
        cout << "Infinty \n";
        return 0;
    }
    return (cosx / sinx);
}

void trigonometry::RunObject()
{
    double num;
    cout << "\n=================================================================================================== \n";
    cout << "*                                Trigonometry                                                     * ";
    cout << "\n=================================================================================================== \n\n";
    cout << "Please enter the Angle: ";
    cin >> num;
    double store = num;
    int value = static_cast<int>(num);
    value = value / 360;
    num = num - (value * 360);
    this->angle = num;
    cout << "\n\n";
    cout << " Sin (" << store << ")   = " << getSin() << endl;
    cout << " Cos (" << store << ")   = " << getCosin() << endl;
    cout << " Tan (" << store << ")   = " << getTangent() << endl;
    cout << " Sec (" << store << ")   = " << getSecant() << endl;
    cout << " Cosec (" << store << ") = " << getCosecant() << endl;
    cout << " Cot (" << store << ")   = " << getCotangent() << endl;

    cout << "\n\n=================================================================================================== \n\n";
    system("pause");
}