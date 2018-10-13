#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
class Vector {
public:
    Vector() : theSize(0), theCapacity(1), data(new int[1]) {}
    explicit Vector(size_t number, int value)
        : theSize(number) , theCapacity(number), data (new int[number]) {
            for (size_t i = 0; i < number; ++i) {
                data[i] = value;
            }
        }

    ~Vector() {
        delete [] data;
    }

    Vector(const Vector& rhs) {
        theSize = rhs.theSize;
        theCapacity = rhs.theCapacity;
        data = new int[theCapacity];
        for (size_t i = 0; i < rhs.theSize; ++i) {
            data[i] = rhs.data[i];
        }
    }

    Vector& operator=(const Vector& rhs) {
        // 1. check self-assignment
        if (this != &rhs) {
            // 2. free up
            delete[] data;

            // 3. allocating
            data = new int[rhs.theCapacity];

            // 4. copying
            theSize = rhs.theSize;
            theCapacity = rhs.theCapacity;
            for (size_t i = 0; i < rhs.theCapacity; ++i) {
                data[i] = rhs.data[i];
            }
        }
        return *this;
    }
    
    void push_back(int val) {
		if (theSize == theCapacity) {
			int* old = data;
			data = new int[2 * theCapacity];
			for (size_t i = 0; i < theSize; ++i) {
				data[i] = old[i]; // *(data + i) // Pointer Arithmetic
			}
			delete[] old;
			theCapacity *= 2;
		}
		data[theSize] = val;
		++theSize;
	}

    size_t size() const { return theSize; }

    void clear() { theSize = 0; }

    void pop_back() { --theSize; }

    int* begin() {
        return data;
    }

    int* begin() {
        return data + theSize;
    }

    // Square brackets?
    int operator[](size_t index) const { 
        return data[index]; 
    } // Getter
    int &operator[](size_t index) { 
        return data[index]; 
    } // Setter

  private:
    int* data;
    size_t theCapacity;
    size_t theSize;
};