#include<iostream>
#include<cstdlib>
#include<string>
#include<sstream>
#include"Calculator.h"
#include"Arithmatic.h"
#include"BigInt.h"
#include"Fraction.h"
#include"Matrix.h"
#include"Set.h"
#include"Trigonometry.h"

void DisplayScreen();
void RunCalculator();

//functions display the main screen of the calculator
void DisplayScreen()
{
	cout << "\n--------------------------------------------------------------------------------------------------- \n";
	cout << "=================================================================================================== \n\n";
	cout << "*                             ADVANCE CALCULATOR                                                  * \n\n";
	cout << "=================================================================================================== \n";
	cout << "--------------------------------------------------------------------------------------------------- \n";
	cout << "\n\n\n";
	cout << "Press these respected number to Run the desired Function \n";
	cout << "1. Arithimatical Operations \n";
	cout << "2. Trigonometric Operations \n";
	cout << "3. Sets Operations \n";
	cout << "4. Matrix Operatinos \n";
	cout << "5. Fractional Operations \n\n";
	cout << "0. Exit \n";
}


//actual functioning of calculator
void RunCalculator()
{
	Calculator** C = new Calculator * [5];
	C[0] = new Arithmatic;
	C[1] = new trigonometry;
	C[2] = new Set;
	C[3] = new matrix;
	C[4] = new MixedFraction;


	string input;
	char ch;
	do
	{
		system("cls");
		DisplayScreen();
		cin >> input;
		cin.ignore();
		ch = input[0];

		switch (ch)
		{
		case '1':
			C[0]->RunObject();
			break;
		case '2':
			C[1]->RunObject();
			break;
		case '3':
			C[2]->RunObject();
			break;
		case '4':
			C[3]->RunObject();
			break;
		case '5':
			C[4]->RunObject();
			break;
		case '0' :
			break;
		default:
			cout << "Opss!!! .... Invalid Input";
			break;
		}

	} while (ch != '0');




	//destroying data
	for (int i = 0; i < 5; i++)
	{
		delete C[i];
	}
	delete[] C;
 
}




int main()
{
	RunCalculator();
	return 0;
}

