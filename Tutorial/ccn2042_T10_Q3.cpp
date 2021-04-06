#include <iostream>
using namespace std;

void printArray(const int [], int);
void multiplyArray(int * const, int, int);

int main(){
	const int arraySize = 10;

	int c[arraySize] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
	
	cout << "Before multiplyArray, array is: ";
	printArray(c, arraySize);

	// Function call on multiplyArray
	// Insert your codes here

	cout << "After multiplyArray, array is: ";
	printArray(c, arraySize);
	
	return 0;
}

void printArray(const int a[], int size){
	for (int i = 0; i < size; i++){
		cout << a[i] << " ";
	}
	cout << endl;
}

// Function definition of multiplyArray
// Insert your codes here
