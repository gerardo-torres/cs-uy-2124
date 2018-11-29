/*
    Copy Control with Inheritance
    Sec 
*/

#include <iostream>
using namespace std;

class Member {
public:
    Member() {
        cerr << "Member()\n";
    }
    Member(const Member& rhs) {
        cerr << "Member(const Member&)\n";
    }
    Member& operator=(const Member& rhs) {
        cerr << "Member::operator=(const Member&)\n";
        return *this;
    }
    ~Member() {
        cerr << "~Member()\n";
    }
};

class Base {
public:
    Base() {
        // Polymorphism turned off when in a constructor
        cerr << "Base()\n";
    }
    Base(const Base& rhs) {
        cerr << "Base(const Base&)\n";
    }
    // Mark destructor as virtual:
    // Without it:if we had a base pointer to a derived, the derived's
    // destructor will not be called
    virtual ~Base() {
        cerr << "~Base()\n";
    }
    Base& operator=(const Base& rhs) {
        cerr << "Base::operator=(const Base&)\n";
        return *this;
    }
};

class Derived : public Base {
public:
    // Derived constructor calls Base constructor
    Derived() {
        cerr << "Derived()\n";
    }
    // Calls non-primitive destructors automatically
    // ~Derived() {
    //     cerr << "~Derived()\n";
    // }
    // Copy: In the initialization list pass in the derived
    // object (rhs) to the Base class
    Derived(const Derived& rhs) : Base(rhs) {
        cerr << "Derived(const Derived&)\n";
    }

    // Assignment:
    Derived& operator=(const Derived& rhs) {
        //*this Base::= rhs;
        //(*this).Base::operator=(rhs);
        //this->Base::operator=(rhs);
        Base::operator=(rhs);
        mem = rhs.mem;
        cerr << "Derived::operator=(const Derived&)\n";
        return *this;
    }
private:
    Member mem;
};

int main() {
    cerr << "Derived der;\n"
         << "------------\n";
    Derived der;
    cout << "===\n";
    cerr << "Derived der2(der);\n"
         << "------------------\n";
    Derived der2(der);
    cout << "===\n";
    cerr << "Derived der3 = der;\n"
         << "-------------------\n";
    Derived der3 = der;
    cout << "===\n";
    cerr << "der = der2;\n"
         << "-----------\n";
    der = der2;
    cout << "===\n";
    cerr << "Derived* p = new Derived();\n"
         << "delete p;\n"
         << "---------------------------\n";
    Derived* p = new Derived();
    delete p;
    cout << "===\n";
    cerr << "Base* bp = new Derived();\n"
         << "delete bp;\n"
         << "---------------------------\n";
    Base* bp = new Derived();
    delete bp;
    cout << "===\n";
}
