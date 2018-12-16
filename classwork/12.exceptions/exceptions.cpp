/*
  CS1124
  Exceptions and Assertions
  Sec. 
*/

#include <iostream>
#include <vector>
#include <cstdlib>

#include <exception>
#include <stdexcept>

//#define NDEBUG
#include <cassert>

using namespace std;

struct OurException {
    
};

void bar(int n) {
    assert (n < 200);
    // vector<int> v;
    // v.push_back(17);
    // cout << v[1] << endl;
    //cout << v.at(1) << endl;
    if (n > 200) {
        // What to do?
        //throw 3.14159;
        throw OurException();
    }
}

void foo(int n) { 
    // vector<int> v;
    // v.push_back(17);
    // cout << v[1] << endl;
    // cout << v.at(1) << endl;
    bar(n); 
}

int main() {
    // vector<int> v;
    // v.push_back(17);
    // cout << v[1] << endl;
    // cout << v.at(1) << endl;
    try {
        foo(300);
    }
    catch(double d) {
        cerr << "Caught a double: " << d << endl;
    }
    // catch (out_of_range oob) {
    //     cerr << "caught an out_of_bounds: " << oob.what() << endl;
    // }
    catch (exception ex) {
        cerr << "caught an exception: " << ex.what() << endl;
    }
    catch (...) {
        cerr << "caught something, don't know what. So long and thanks for all the fish.\n";
    }
    cerr << "still going\n";
}
