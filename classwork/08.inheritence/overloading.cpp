/*
  Demonstrates that the compiler makes the choice for overloading
 */

#include <iostream>
using namespace std;

class Parent {};
class Child : public Parent {};
class GrandChild : public Child {};

void func(Parent& base) { cout << "func(Parent)\n"; }
void func(Child& derived) {cout << "func(Child)\n"; }
void func(Child& derived, Parent& base) {cout << "func(Child, Parent)\n"; }
void func(Parent& base, Child& derived) {cout << "func(Parent, Child )\n"; }
  
void otherFunc(Parent& base) {
    func(base);
}

int main() {
    Parent par;
    func(par);
    Child child;
    func(child);
    
    //func(child, child);

    GrandChild gc;
    func(gc);

    otherFunc(child);

}
