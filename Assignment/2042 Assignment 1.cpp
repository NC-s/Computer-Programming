// CCN2042 Assignment 1
// Program template file: A1Template.cpp
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

void showInfo()
{
	cout << "Name      : #########\n";
	cout << "Student ID: #########\n";
	cout << "Class     : #########\n";

}

void Q1()
{
	double x1, x2, y1, y2;                                    // Use double data type to allow user input decimal data

	cout << "Input (x1, y1): ";                               // Prompt the user to enter the x-coordinates and y-coordinates of two points
	cin >> x1 >> y1;
    
	cout << "Input (x2, y2): ";
	cin >> x2 >> y2;

	double distance = sqrt((y2 - y1)*(y2 - y1) + (x2 - x1)*(x2 - x1));
	cout << "The distance is " << fixed << setprecision(3) << distance << " units" << endl;  // Use fixed and setprecision(x) function to get 3 decimal place result
}

void Q2()
{
	int num;
	int digit;
	int largest = 0;
	bool flag = false;

	cout << "Input a positive integer with 2 to 9 digits: ";  // Prompt the user to input any positive integer value with 2 to 9 digits
	cin >> num;
	
	while (flag == false)
	{
		if ((num > 9 && num < 1000000000))    // Check the value of input is in range or not
		{	
			digit = num % 100;                // Using % 100 to reach 2-digit data
			while (digit > largest)           // Compare the data and save the larger one
				largest = digit;
			num = num / 10;                   // Using / 10 to change the value and get another group of data
			if (num < 10)
			flag = true;
		}
		else {
			cout << "Error: Out-of-range. Input again: ";     // Display the error message and allow user to input again
			cin >> num;
		}
	}
    cout << "The largest 2-digit value is " << largest << endl;
}

void Q3()
{
	int size, i, j;
	cout << "Input size (1 to 10): ";         // Prompt the user to input the size within 1 to 10
	do {
		cin >> size;
		if (size < 1 || size > 10)            // Check the user's input of size within range or not
			cout << "Error: Out-of-range. Input again: ";     // Display the error message and allow user to input again
		else
			for(i = 0; i < 3 * size; i++){    
				for(j = 0; j < 3 * size; j++)
					if((j / size == 1 && i / size != 1) || (j / size != 1 && i / size == 1))  // (int / int) has no decimal so the formula will create the correct X-shaped cross pattern printouts
						cout << ' ';
					else
						cout << '*';
				cout << endl;
		}
		}
		while (size < 1 || size > 10);
}

// GIVEN CODES, DO NOT MODIFY 
// BEGIN
int main()
{
	int prog_choice;

	showInfo();

	do {
		cout << endl;
		cout << "Assignment One - Program Selection Menu" << endl;
		cout << "---------------------------------------" << endl;
		cout << "(1) Program One" << endl;
		cout << "(2) Program Two" << endl;
		cout << "(3) Program Three" << endl;
		cout << "(4) Exit" << endl;
		cout << "Enter the choice: ";
		cin >> prog_choice;

		switch (prog_choice){
		case 1: Q1(); break;
		case 2: Q2(); break;
		case 3: Q3(); break;
		case 4: break;
		default: 
			cout << "Please enter choice 1 - 4 only." << endl;
			break;
		}
	} while (prog_choice != 4);

	cout << "Program terminates. Good bye!" << endl;
	return 0;
}
// END