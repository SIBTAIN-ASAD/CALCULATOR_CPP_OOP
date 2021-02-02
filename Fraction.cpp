#include<iostream>
#include"Fraction.h"
#include<cstdlib>
using namespace std;


//================================================================================================
// Fraction class Implimentation
//================================================================================================

MixedFraction::MixedFraction() // Initialize data members to default values. Remember denominator must not be zero. 
{
    this->integer = 0;
    this->numerator = 0;
    this->denominator = 1;
}

MixedFraction::MixedFraction(int a_integer, int a_nmrator, int a_dnmnator)// Initialize data members with parameter values. 
{
    //setting value of intiger
    this->integer = a_integer;

    //setting value of denumirator
    if (a_nmrator >= 0)
    {
        this->numerator = a_nmrator;
    }
    else
    {
        cout << "Invalid input for numerator \n";
        cout << "numerator set to zero";
        this->numerator = 0;
    }

    //setting the value of denominator
    if (a_dnmnator > 0)
    {
        this->denominator = a_dnmnator;;
    }
    else
    {
        cout << "Invalid input for denumerator \n";
        cout << "denumerator set to one\n";
        this->denominator = 1;
    }

}

MixedFraction::MixedFraction(int a_integer) // Constructor with only integer part, set fractional part to zero.
{
    this->integer = a_integer;
    this->numerator = 0;
    this->denominator = 1;
}

MixedFraction::MixedFraction(const MixedFraction& a_mFrac) // copy constructor.
{
    this->integer = a_mFrac.integer;
    this->numerator = a_mFrac.numerator;
    this->denominator = a_mFrac.denominator;
}

MixedFraction::~MixedFraction() // Destructor should display message “Object is destroyed”. 
{
    cout << " ";
}

void MixedFraction::setIntegralPart(int a_intgr)
{
    this->integer = a_intgr;
}

bool MixedFraction::setDenominator(int a_dnmnator)
{
    if (a_dnmnator > 0)
    {
        this->denominator = a_dnmnator;
        return true;
    }
    else
    {
        return false;
    }
}

void MixedFraction::setNumerator(int a_nmrator)
{
    if (a_nmrator >= 0)
    {
        this->numerator = a_nmrator;
    }
    else
    {
        cout << "Invalid input for numerator \n";
        cout << "numerator set to zero";
        this->numerator = 0;
    }


}
int MixedFraction::getIntegralPart() const //getter for intiger part
{
    return integer;
}

int MixedFraction::getDenominator() const //getter for denominator
{
    return denominator;
}
int MixedFraction::getNumerator()const //getter for numerator
{
    return numerator;
}

double MixedFraction::evaluate() // should return the decimal equivalent of the mixed number. 
{
    double val;
    double integ = static_cast<double>(integer);
    double num = static_cast<double>(numerator);
    double den = static_cast<double>(denominator);
    val = integ + (num / den);
    return val;
}

void MixedFraction::display() // should display the fraction in proper format i.e. 3 2/5.
{
    cout << this->integer << " " << this->numerator << "/" << this->denominator;
}

MixedFraction MixedFraction::operator+(const MixedFraction& fraction) // overload binary + operator. 
{
    MixedFraction result;
    int nom = 0;
    int den = 0;

    nom = (fraction.denominator * (this->denominator * this->integer + this->numerator)) + (this->denominator * (fraction.denominator * fraction.integer + fraction.numerator));
    den = this->denominator * fraction.denominator;

    result.integer = nom / den;
    result.numerator = nom % den;
    result.denominator = den;
    return result;
}

MixedFraction MixedFraction::operator-(const MixedFraction& fraction) // overload binary – operator. 
{
    MixedFraction result;
    int nom = 0;
    int den = 0;

    nom = (fraction.denominator * (this->denominator * this->integer + this->numerator)) - (this->denominator * (fraction.denominator * fraction.integer + fraction.numerator));
    den = this->denominator * fraction.denominator;

    result.integer = nom / den;
    result.numerator = nom % den;
    result.denominator = den;
    return result;
}

MixedFraction MixedFraction::operator*(const MixedFraction& fraction) // overload binary * operator. 
{
    MixedFraction result;
    int nom = 0;
    int den = 0;

    nom = (this->denominator * this->integer + this->numerator) * (fraction.denominator * fraction.integer + fraction.numerator);
    den = this->denominator * fraction.denominator;

    result.integer = nom / den;
    result.numerator = nom % den;
    result.denominator = den;

    return result;
}

MixedFraction MixedFraction::operator/(const MixedFraction& fraction) // overload binary / operator.
{
    MixedFraction result;
    int nom = 0;
    int den = 0;

    nom = (this->denominator * this->integer + this->numerator) * fraction.denominator;
    den = this->denominator * (fraction.denominator * fraction.integer + fraction.numerator);

    result.integer = nom / den;
    result.numerator = nom % den;
    result.denominator = den;

    return result;
}


bool MixedFraction::operator==(MixedFraction& fraction) // overload relational == operator
{
    if (this->evaluate() == fraction.evaluate())
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool MixedFraction::operator<(MixedFraction& fraction) // overload relational < operator.
{
    if (this->evaluate() < fraction.evaluate())
    {
        return true;
    }
    else
    {
        return false;
    }
}


MixedFraction MixedFraction::operator-() // overload unary – operator.
{
    MixedFraction result;
    if (this->integer != 0)
    {
        result.integer = -1 * this->integer;
        result.numerator = this->numerator;
        result.denominator = this->denominator;
    }
    else
    {
        result.integer = this->integer;
        result.numerator = -1 * this->numerator;
        result.denominator = this->denominator;
    }

    return result;
}


MixedFraction MixedFraction::operator++() // overload pre-increment operator.
{
    (this->integer)++;
    return *this;
}


MixedFraction MixedFraction::operator++(int) // overload post-increment operator.
{
    MixedFraction curr(integer, numerator, denominator);
    (this->integer)++;
    return curr;
}


MixedFraction MixedFraction::operator+=(const MixedFraction& fraction) // overload combined operator +=
{
    int nom = 0;
    int den = 0;

    nom = (fraction.denominator * (this->denominator * this->integer + this->numerator)) + (this->denominator * (fraction.denominator * fraction.integer + fraction.numerator));
    den = this->denominator * fraction.denominator;

    this->integer = nom / den;
    this->numerator = nom % den;
    this->denominator = den;
    return *this;
}


MixedFraction MixedFraction::operator/=(const MixedFraction& fraction) // overload combined operator /=
{
    int nom = 0;
    int den = 0;

    nom = (this->denominator * this->integer + this->numerator) * fraction.denominator;
    den = this->denominator * (fraction.denominator * fraction.integer + fraction.numerator);

    this->integer = nom / den;
    this->numerator = nom % den;
    this->denominator = den;

    return *this;
}


MixedFraction MixedFraction::operator=(const MixedFraction& fraction) //overloading equal operator
{
    this->integer = fraction.integer;
    this->numerator = fraction.numerator;
    this->denominator = fraction.denominator;
    return *this;
}


void MixedFraction::RunObject() // fucntion to check the fraction class
{
    cout << "\n=================================================================================================== \n";
    cout << "*                                Fraction                                                         * ";
    cout << "\n=================================================================================================== \n\n";
    MixedFraction frac1;
    MixedFraction frac2;
    MixedFraction frac3;
    int num;
    //******* input of first fraction ********
    cout << "\n******* input of first fraction ********\n\n";
    cout << "Integral part: ";
    cin >> num;
    frac1.setIntegralPart(num);
    cout << "Numerator: ";
    cin >> num;
    frac1.setNumerator(num);
    cout << "Demoninator: ";
    cin >> num;
    if (!(frac1.setDenominator(num)))
    {
        cout << "Please enter a valid number ( > 0) : ";
        cin >> num;
    }

    //******* input of second fraction ********
    cout << "\n******* input of second fraction ******** \n\n";
    cout << "Integral part: ";
    cin >> num;
    frac2.setIntegralPart(num);
    cout << "Numerator: ";
    cin >> num;
    frac2.setNumerator(num);
    cout << "Demoninator: ";
    cin >> num;
    if (!(frac2.setDenominator(num)))
    {
        cout << "Please enter a valid number ( > 0) : ";
        cin >> num;
    }

    cout << "\n********************************************************";
    cout << "\nFraction A: (";
    frac1.display();
    cout << ") or " << frac1.evaluate();
    cout << "\nFraction B: (";
    frac2.display();
    cout << ") or " << frac2.evaluate() << endl;

    cout << "\nPress these respected number to run the desired function \n";
    cout << "1. Sum \n";
    cout << "2. Subtract \n";
    cout << "3. Multiply \n";
    cout << "4. Divide \n";
    cout << "5. Compare the fractions \n";
    cout << "0. Exit \n";


    string input;
    char ch;

    cin >> input;
        cin.ignore();
        ch = input[0];

        switch (ch)
        {
        case '1':
            frac3 = frac1 + frac2;
            cout << "(";
            frac1.display();
            cout << ") + (";
            frac2.display();
            cout << ") = (";
            frac3.display(); 
            cout << ")  or  " << frac3.evaluate() << endl;
            break;
        case '2':
            frac3 = frac1 - frac2;
            cout << "(";
            frac1.display();
            cout << ") - (";
            frac2.display();
            cout << ") = (";
            frac3.display();
            cout << ")  or  " << frac3.evaluate() << endl;
            break;
        case '3':
            frac3 = frac1 * frac2;
            cout << "(";
            frac1.display();
            cout << ") * (";
            frac2.display();
            cout << ") = (";
            frac3.display();
            cout << ")  or  " << frac3.evaluate() << endl;
            break;
        case '4':
            frac3 = frac1 / frac2;
            cout << "(";
            frac1.display();
            cout << ") / (";
            frac2.display();
            cout << ") = (";
            frac3.display();
            cout << ")  or  " << frac3.evaluate() << endl;
            break;
        case '5':
            if (frac1 == frac2)
            {
                cout << "\nThe fractions are equal \n";
            }
            else
            {
                cout << "\nThe fractions not are equal \n";
            }

            if (frac1 < frac2)
            {
                cout << "\nThe fraction 1 is smaller than 2 \n";
            }
            else
            {
                cout << "\nThe fraction 2 is smaller than 1 \n";
            }            break;
        case '0':
            break;
        default:
            cout << "\nOpss!!! .... Invalid Input";
            break;
        }

    cout << "\n=================================================================================================== \n\n";

    system("pause");
}


//int main()
//{
//    MixedFraction F;
//    F.RunObject();
//
//    return 0;
//}