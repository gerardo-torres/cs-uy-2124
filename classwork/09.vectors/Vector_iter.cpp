/*
  Vector Class
  Basic vector of ints
  Sec ??
 */
#include <vector>
#include <iostream>
using namespace std;

class Iterator {
    friend bool operator!=(const Iterator& lhs, const Iterator& rhs) {
        return lhs.where != rhs.where;
    }
public:
    Iterator(int* p) : where(p) {}
    Iterator& operator++() {
        ++where;
        return *this;
    }
    int operator*() const {
        return *where;
    }
    int& operator*() {
        return *where;
    }
private:
    int* where;

};


class Vector {
public:
    
    // default constructor
    Vector() : data(nullptr), theSize(0), theCapacity(0)  {}
    explicit Vector(size_t howMany, int val=0)
    {
        theSize = howMany;
        theCapacity = howMany;
        data = new int[howMany];
        for (size_t i = 0; i < theSize; ++i) {
            data[i] = val;
        }
    }

    // Copy control
    ~Vector() {
        delete [] data;
    }
    Vector(const Vector& rhs) {
        theSize = rhs.theSize;
        theCapacity = rhs.theCapacity;
        data = new int[theCapacity];
        for (size_t i = 0; i < theSize; ++i) {
            data[i] = rhs.data[i];
        }
    }
    // lhs = rhs
    Vector& operator=(const Vector& rhs) {
        if (this != &rhs) {
            // Free up the old (destructor)
            delete [] data;
            // Allocate new
            data = new int[rhs.theCapacity];
            // Copy all the stuff
            theSize = rhs.theSize;
            theCapacity = rhs.theCapacity;
            for (size_t i = 0; i < theSize; ++i) {
                data[i] = rhs.data[i];
            }
        }
        // Return ourselves
        return *this;
    }


    void push_back(int val) {
        if (theSize == theCapacity) {
            if (data == nullptr) {
                data = new int[1];
                theCapacity = 1;
            } else {
                int* oldData = data;
                data = new int[2*theCapacity];
                for (size_t i = 0; i < theSize; ++i) {
                    data[i] = oldData[i];
                }
                delete [] oldData;
                theCapacity *= 2;
            }
        }
        data[theSize] = val;
        ++theSize;
    }

    size_t size() const { return theSize; }
    void pop_back() { --theSize; }

    void clear() { theSize = 0; };


    // Square brackets?
    int operator[](size_t index) const {
        return data[index];
    }
    int& operator[](size_t index) {
        return data[index];
    }

    Iterator begin() { 
        //return Iterator(data); 
        Iterator result(data);
        return result;
    }
    Iterator end() { return Iterator(data+theSize); }


    Iterator begin() const { return Iterator(data); }
    Iterator end() const { return Iterator(data+theSize); }


private:
    int* data;
    size_t theSize;
    size_t theCapacity;
};


//void print(vector<int>& v) {
void print(const vector<int>& v) {
    //for (int val : v) {
    for (int& val : v) {
        cout << val << ' ';
        ++val;
    }
    cout << endl;
}

void print(const Vector& v) {
    //for (int val : v) {
    for (int& val : v) {
        cout << val << ' ';
        ++val;
    }
    cout << endl;
}


int main() {

    // Not templated.  Our Vector class can only hold ints.
    Vector v;  

    v.push_back(17);
    v.push_back(42);
    v.push_back(6);
    v.push_back(28);
    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i] << ' ';
        //cout << v.operator[](i) << endl;
    }
    cout << endl;
    
    v[0] = 100;

    //    v[0];
    //Vector v2(v);
    Vector v2 = v;
    for (size_t i = 0; i < v2.size(); ++i) {
        cout << v2[i] << ' ';
    }
    cout << endl;

    Vector v3;
    v3 = v;

    //v3 = 17;
    v3 = Vector(17);

    for (int val : v2) {
        cout << val << ' ';
        ++val;
    }
    cout << endl;

    //    for (int* p = v2.begin(); p != v2.end(); ++p) {
    for (Iterator p = v2.begin(); p != v2.end(); ++p) {
        int x = *p;   // p.operator*()
        cout << x << endl;
    }

    print(v2);
    print(v2);
}

