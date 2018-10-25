/*
   Arithmetic Operator Overloading
   Sec F
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Complex {
    friend ostream& operator<<(ostream& os, const Complex& rhs) {
        os << rhs.real;
        if (rhs.imaginary >= 0) os << '+';
        os << rhs.imaginary << 'i';
        return os;
    }
public:
    Complex() : real(0), imaginary(0) {}
    Complex(double real) : real(real), imaginary(0) {}
    Complex(double real, double imag) : real(real), imaginary(imag) {}

    // a lot like an assignment operator
    // doesnt need to be a friend it just uses the plus equals operator
    Complex& operator+=(const Complex& rhs) {
        // this->real += rhs.real;
        // this->imaginary += rhs.imaginary;
        real += rhs.real;
        imaginary += rhs.imaginary;
        return *this; 
    }

    // return by refernce we return ourselves
    Complex& operator++() {
        ++real;
        return *this;
    }

    // c1++
    // const Complex& operator++(int dummy) { // NO!!
    Complex operator++(int dummy) {
        Complex result(*this);
        ++real;
        return result;
    }

    explicit operator bool() const {
        return real != 0 || imaginary != 0;
    }
    
    bool operator==(const Complex& rhs) const {
        return rhs.imaginary == imaginary && rhs.real == real;
    }
private:
    double real, imaginary;
};

//const Complex& operator+(const Complex& lhs, const Complex& rhs) { // NO!
Complex operator+(const Complex& lhs, const Complex& rhs) {
    Complex result = lhs;
    result += rhs;
    return result;
}

int main() {
    Complex c1;         // 0+0i
    Complex c2(17);     // 17+0i
    Complex c3(3, -5);  // 3-5i
    cout << "c1: " << c1 << endl
         << "c2: " << c2 << endl
         << "c3: " << c3 << endl;
    c1 = c2 + c3;
    operator+(c2, c3);
    //c2.operator+(c3);

    // c1 += c2;
    //    operator+=(c1, c2);
    c1.operator+=(c2);

    ++c1;
    //operator++(c1);
    c1.operator++();

    c1++;
    c1.operator++(0);

    if (c1) {}

    if (c1 == c2) {}

    if (c1 == c1) {
        cout << "c1 == c1\n";
    }

    Complex c4(1);

    if (c1 == c4) {
        cout << "c1 == c4\n";
    } else {
        cout << "c1 != c4\n";
    }
}
