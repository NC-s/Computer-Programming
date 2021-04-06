#include <iostream>
#include <iomanip>
using namespace std;

int main() 
{
	int n, sum = 0, count = 0;

	do {
		cout << "Input an integer: ";
		cin >> n;
		if (n > 0) {
		sum += n;
		count += 1;
		}
	} while (n != 0);

	cout << "Average of positive values is " << fixed << setprecision(3) << (float) sum/count << endl;

	return 0;
}