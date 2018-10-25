/*
Author:         Gerardo Torres
Class:          CS-UY 2124
File Name:      rec08.cpp
-------------------------------------------------------------
Description:    Implementing a rational number class. Focus
                on operator overloading to perform operations
                with this class.
-------------------------------------------------------------
compile:        $ g++ rec08.cpp -o rec08
run:            $ ./rec08
*/

#include <iostream>
#include <string>

using namespace std;

class Rational {
    // Input operator
    friend istream& operator>>(istream& is, Rational& rhs) {
        char divided;
        int left, right;
        is >> left >> divided >> right;
        rhs.numer = left;
        rhs.denom = right;
        rhs.normalize();
        return is;
    }
    
    friend bool operator==(const Rational& lhs, const Rational& rhs) {
        return lhs.numer == rhs.numer && lhs.denom == rhs.denom;
    }
    
    // Output operator
    friend ostream& operator<<(ostream& os, const Rational& rhs) {
        os << rhs.numer << '/' << rhs.denom;
        return os;
    }
    
    // greater than
    friend bool operator>(const Rational& lhs, const Rational& rhs) {
        int newBottom = lhs.denom * rhs.denom;
        int leftTop = lhs.numer * rhs.denom;
        int rightTop = rhs.numer * lhs.denom;
        return (leftTop - rightTop) > 0;
    }

public:
    
    Rational(int num = 0, int num2 = 1) 
    : numer(num), denom(num2) {
        normalize();
    }

    void normalize() {
        if (numer > 0 && denom < 0) {
            denom *= -1;
            numer *= -1;
        }
        if (numer < 0 && denom < 0) {
            numer *= -1;
            denom *= -1;
        } 
        int gcd = greatestCommonDivisor(abs(numer), abs(denom));
        numer /= gcd;
        denom /= gcd;
    }

    int greatestCommonDivisor(int x, int y) const {
        while (y != 0) {
            int temp = x % y;
            x = y;
            y = temp;
        }
        return x;
    }

    Rational& operator+=(const Rational& rhs) {
        int newDenom = denom * rhs.denom;
        int leftNumer = numer * rhs.denom;
        int rightNumer = rhs.numer * denom;
        int newNumer = leftNumer + rightNumer;
        numer = newNumer;
        denom = newDenom;
        normalize();
    }

    // Pre
    Rational& operator++() {
        *this += 1;
        return *this;
    }

    // Post
    Rational operator++(int dummy) {
        Rational temp = *this;
        *this += 1;
        return (temp);
    }

    explicit operator bool() const {
        return !(numer == 0);
    }
private:
    int numer;
    int denom;
};

// Non-member operator overload for +
Rational operator+(Rational& lhs, const Rational& rhs) {
    Rational result(lhs);
    result += rhs;
    return result;
}


bool operator!=(const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs);
}

// Pre
Rational& operator--(Rational& rhs) {
    rhs += -1;
    return rhs;
}

// Post
Rational operator--(Rational& rhs, int dummy) {
    Rational temp(rhs);
    rhs += -1;
    return temp;
}

// less than
bool operator<(const Rational& lhs, const Rational& rhs) {
    return !(lhs > rhs);
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
    return (lhs > rhs) || (lhs == rhs);
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
    return !(lhs > rhs) || (lhs == rhs);
}

int main() {
    Rational twoThirds(2,3);
    cout << twoThirds << endl;
    
    Rational a, b;
    cout << "Input two rational numbers.\n";
    cout << "a: ";
    cin >> a;
    cout << "b: ";
    cin >> b;
    Rational one(1);

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "one = " << one << endl;
    cout << "a += b: " << (a += b) << endl;	// Implement as member
    cout << "a = " << a << endl;
    
    // Implement as non-member, but not a friend
    cout << "a + one: " << (a + one) << endl;
    cout << "a == one: " << boolalpha << (a == one) << endl;
    
    // How does this manage to work?
    // It does NOT require writing another == operator. 
    cout << "1 == one: " << boolalpha << (1 == one) << endl;
    
    // Do not implement as friend.
    cout << "a != one: " << boolalpha << (a != one) << endl;

    cout << "a = " << a << endl;
    cout << "++a = " << (++a) << endl;
    cout << "a = " << a << endl;
    cout << "a++ = " << (a++) << endl;
    cout << "a = " << a << endl;
    cout << "--a = " << (--a) << endl;
    cout << "a = " << a << endl;
    cout << "a-- = " << (a--) << endl;
    cout << "a = " << a << endl;

    cout << "++ ++a = " << (++ ++a) << endl;
    cout << "a = " << a << endl;
    cout << "-- --a = " << (-- --a) << endl;
    cout << "a = " << a << endl;

    cout << "a++ ++ = " << (a++ ++) << endl;
    cout << "a = " << a << endl;

    // Even though the above example, (a++ ++), compiled, the
    // following shouldn't.
    // But some compiler vendors might let it...  Is your compiler
    // doing the right thing?
    // cout << "a-- -- = " << (a-- --) << endl;
    // cout << "a = " << a << endl;

    Rational eightFifths(8, 5);
    Rational sevenhalves(7, 2);
    if (eightFifths > sevenhalves) {
        cout << "7/2 is smaller than 8/5\n";
    } else {
        cout << "8/5 is smaller than 7/2\n";
    }

    if (eightFifths < sevenhalves) {
        cout << "8/5 is smaller than 7/2\n";
    } else {
        cout << "7/2 is smaller than 8/5\n";
    }

    Rational fourHalves(4, 2);
    Rational eightQuarters(8, 4);

    if (fourHalves >= eightQuarters) {
        cout << "4/2 >= 8/4\n";
    } else {
        cout << "8/3 >= 42\n";
    }

    if (Rational(1)) {
        cout << "1 is true" << endl;
    } else {
        cout << "1 is false" << endl;
    } 
    if (Rational(0)) {
        cout << "0 is true" << endl;
    } else {
        cout << "0 is false" << endl;
    } 
}

