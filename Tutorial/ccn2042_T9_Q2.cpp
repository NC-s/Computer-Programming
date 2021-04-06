#include <iostream>
using namespace std;

void swapString(char [], char []);	// prototype

int main() {

	char w1[20], w2[20];

	cout << "Enter the two words (separated by space): ";
	cin >> w1;
	cin >> w2;

	cout << "Before swapping, words are:\n";
	cout << w1 << endl << w2 << endl;

	// Function call on swapString
	// Insert your code here
	
	cout << "After swapping, words are:\n";
	cout << w1 << endl << w2 << endl;

	return 0;
}

// Function definition of swapString
// Insert your codes here
