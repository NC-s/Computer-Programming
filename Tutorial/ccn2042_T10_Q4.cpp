#include <iostream>
using namespace std;

int main() {
	char *buffer = new char [100];	// reserve 100 characters
	char *word[10] = {};			// initialize all pointers to 0 (NULL)

	// Your code should be inserted here

	for (int i = 0; i < 10; i++)
		if (word[i] != 0)			// check if it is a NULL pointer
			cout << i << ": " << word[i] << endl;

	return 0;
}