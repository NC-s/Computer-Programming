#include <iostream>
#include <cstring>
using namespace std;

int main(){
	char buffer[80];
	char msgs[10][15] = {
		"a", "ab", "abc", "abcd", "abcde", "abcdef", 
		"abcdefg", "abcdefgh", "abcdefghi", "abcdefghij"
	};
	
	// Put strings in msgs into buffer
	// Your codes should be inserted here.
	
	// Print the buffer content
	cout << "buffer is:" << endl;
	cout << buffer;

	// Show the length of buffer, using strlen()
	// Your codes should be inserted here.

	return 0;
}
