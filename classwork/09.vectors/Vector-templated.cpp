/*
  Vector Class
  Templated vector
  Sec F
 */
#include <iostream>
using namespace std;

//template <class Fred>
template <typename Fred>
class Vector {
public:
    
    // default constructor
    Vector() : data(nullptr), theSize(0), theCapacity(0)  {}
    //explicit Vector(size_t howMany, int val=0)
    explicit Vector(size_t howMany, Fred val = Fred())
    {
        theSize = howMany;
        theCapacity = howMany;
        //data = new int[howMany];
        data = new Fred[howMany];
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
        //        data = new int[theCapacity];
        data = new Fred[theCapacity];
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
            //data = new int[rhs.theCapacity];
            data = new Fred[rhs.theCapacity];
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


    void push_back(Fred val) {
        if (theSize == theCapacity) {
            if (data == nullptr) {
                data = new Fred[1];
                theCapacity = 1;
            } else {
                Fred* oldData = data;
                data = new Fred[2*theCapacity];
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
    const Fred& operator[](size_t index) const {
        return data[index];
    }
    Fred& operator[](size_t index) {
        return data[index];
    }
    
private:
    Fred* data;
    size_t theSize;
    size_t theCapacity;
};

template <class T>
void printVec(const Vector<T>& vec) {
    
}

int main() {

    // Not templated.  Our Vector class can only hold ints.
    Vector<int> v;  
    printVec(v);

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

    for (int val : v2) cout << val << ' ';
    cout << endl;
}

