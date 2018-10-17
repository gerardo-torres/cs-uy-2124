#include <iostream>
using namespace std;

// Note the "= 5" after the parameter name y.
// This allows us to call the function foo passing it either
// two arguments or just one argument.  When the second argument
// is omitted in a call to foo, then the parameter y will have
// the default value, which is specified here to be 5.
void foo(int x, int y = 5) {
	cout << "x = " << x << ", y = " << y << endl;
}

int main () {
	foo(17);
	foo(17, 0);
	return 0;
}

