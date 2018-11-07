/*
  Demonstrates that the compiler makes the choice for overloading
 */

#include <iostream>
using namespace std;

class Parent {
public:
    virtual void whereami() const { 
        cout << "Parent" << endl; 
    }
};
class Child : public Parent {
public:
    void whereami() const { 
        cout << "Child!!!" << endl; 
    }
};

void func(const Parent& base) { cout << "func(Parent)\n"; }
void func(const Child& derived) {cout << "func(Child)\n"; }
  
void otherFunc(Parent& base) {
    func(base);
    base.whereami();
}

int main() {
    Child child;
    otherFunc(child);
}
