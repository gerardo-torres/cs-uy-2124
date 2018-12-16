/*
  Recursion
  Sec F

  See code in Linked Lists for recursive listClear and list duplicate
*/

#include <iostream>
using namespace std;


void towers(int count, char start, char target, char spare) {
    if (count == 1) {
        cout << "move disk: " << count << " from spindle " 
             << start << " to spindle " << target << endl;
    } else {
        towers(count - 1, start, spare, target);
        cout << "move disk: " << count << " from spindle " 
             << start << " to spindle " << target << endl;;
        towers(count - 1, spare, target, start);    
    }
}

void towers2(int count, char start, char target, char spare) {
    if (count > 0) {
        towers2(count - 1, start, spare, target);
        cout << "move disk: " << count << " from spindle " 
             << start << " to spindle " << target << endl;
        towers2(count - 1, spare, target, start);    
    }
}

void printDigits(int n) {
    if (n < 10) {
        cout << n << ' ';
    }
    else {
        printDigits(n/10);
        cout << n % 10 << ' ';
    }
}

int main() {
    towers(3, 'A', 'C', 'B');
    cout << "=========\n";
    towers2(3, 'A', 'C', 'B');
    printDigits(123456);
    cout << endl;
}
