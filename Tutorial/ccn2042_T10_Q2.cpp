#include <iostream>
using namespace std;
void swapInteger(int *, int *);

int main(){
	int x = 2, y = 5;
	
	cout << "Before swapping:" << endl;
	cout << "x is: " << x << endl;
	cout << "y is: " << y << endl;
	
	swapInteger(&x, &y);

	cout << "After swapping:" << endl;
	cout << "x is: " << x << endl;
	cout << "y is: " << y << endl;
	
	return 0;
}
void swapInteger(int *a, int b) {
	int n = *a;
	*a = *b;
	*b = n;
}
