#include <iostream>
using namespace std;

// Function prototype is inserted here

int main(){
	int lower, upper, sum;
	float average;

	cout << "Enter the lower bound: ";
	cin >> lower;
	cout << "Enter the upper bound: ";
	cin >> upper;

	sumAvg(lower, upper, sum, average);

	cout << "From " << lower << " to " << upper << ":\n";
	cout << "Sum     = " << sum << endl;
	cout << "Average = " << average << endl;

	return 0;
}

// Function definition is inserted here