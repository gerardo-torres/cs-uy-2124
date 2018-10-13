/*
Author:         Gerardo Torres
Class:          CS-UY 2124
File Name:      rec06.cpp
-----------------------------------------------------------
Description:    Modeling a directory of employees with focus
                on Dynamic arrays and copy control
-----------------------------------------------------------
compile:        $ g++ rec06.cpp -o rec06
run:            $ ./rec06
*/

#include <string>
#include <iostream>
using namespace std;

class Position {
    friend ostream &operator<<(ostream &os, const Position &rhs) {
        os << '[' << rhs.title << ',' << rhs.salary << ']';
        return os;
    }

public:
    Position(const string &aTitle, double aSalary)
    : title(aTitle), salary(aSalary) {}
   
    const string &getTitle() const { 
        return title; 
    }

    double getSalary() const { 
        return salary; 
    }
    
    void changeSalaryTo(double d) { 
        salary = d;
    }

private:
    string title;
    double salary;
}; // class Position

class Entry {
    friend ostream &operator<<(ostream &os, const Entry &rhs) {
        os << rhs.name << ' ' << rhs.room
            << ' ' << rhs.phone << ", " << *rhs.pos;
        return os;
    }

public:
    Entry(const string &name, unsigned room, unsigned phone, Position &position)
        : name(name), room(room), phone(phone), pos(&position){
    }

    const string &getName() const { 
        return name; 
    }
    
    const unsigned &getPhone() const { 
        return phone; 
    }

private:
    string name;
    unsigned room;
    unsigned phone;
    Position *pos;
}; // class Entry

class Directory {
    // Overload output operator
    friend ostream &operator<<(ostream& os, const Directory& rhs) {
        for (size_t i = 0; i < rhs.size; ++i) {
            os << *rhs.entries[i] << '\n';
        }
        return os;
    }

public:

    Directory()
    : size(0), capacity(1), entries(new Entry*[capacity]) { 
        /*constructor for `Directory d;` */
    }

    // Assignment operator
    Directory& operator=(const Directory& rhs) {
        // Check for self-assignment
        if (this != &rhs) {
            // Get rid of your current entries (if they exist...)
            for (size_t i = 0; i < size; ++i) {
                delete entries[i];
            }
            delete [] entries;
            size, capacity = rhs.size, rhs.capacity;
            // New empty entries
            entries = new Entry*[capacity];
            for (size_t i = 0; i < size; ++i) {
                Entry *currEntry = rhs.entries[i];  // Current reading Entry
                entries[i] = new Entry(*currEntry); // New Entry object allocated to the heap
            }
        }
        // Return yourself
        return *this;
    }

    // Copy constructor
    Directory(const Directory& rhs)
    : size(rhs.size), capacity(rhs.capacity) {
        entries = new Entry*[capacity];
        for (size_t i = 0; i < size; ++i) {
            Entry* currEntry = rhs.entries[i];      // Current reading Entry
            entries[i] = new Entry(*currEntry);     // New Entry object allocated to the heap
        }
    }

    ~Directory() {
        cout << "Deleting Directory\n";
        for (size_t i = 0; i < size; ++i) {
            delete entries[i];  // Deleting entries from heap
        }
        delete[] entries;       // Deleting array from heap
    }

    void add(const string &name, unsigned room, unsigned ph, Position &pos) {
        // Check if size will exceeed capacity
        if (size == capacity) {
            Entry **oldEntries = entries;
            capacity *= 2;
            entries = new Entry *[capacity];
            for (size_t i = 0; i < size; ++i) {
                entries[i] = oldEntries[i];
            }
            delete[] oldEntries;
        } // if
        entries[size] = new Entry(name, room, ph, pos);
        ++size;
    } // add

    int operator[](const string& name) {
        for (size_t i = 0; i < size; i++){
            if (name == entries[i]->getName()){
                return entries[i]->getPhone();
            }
        }
        cerr << "Name: " << name << " not found!\n";
    }

private:
    size_t size;
    size_t capacity;
    Entry **entries;
}; // class Directory

void doNothing(Directory dir) { 
    // Pass Directory by value (NOT by reference)
    cout << dir << endl; 
}

int main() {

    // Note that the Postion objects are NOT on the heap.
    Position boss("Boss", 3141.59);
    Position pointyHair("Pointy Hair", 271.83);
    Position techie("Techie", 14142.13);
    Position peon("Peonissimo", 34.79);

    // Create a Directory
    Directory d;
    d.add("Marilyn", 123, 4567, boss);
    // cout << "i'm trying to display d\n";
    cout << d << endl;
    // cout << "back from displaying d\n";

    Directory d2 = d; // What function is being used??
    d2.add("Gallagher", 111, 2222, techie);
    d2.add("Carmack", 314, 1592, techie);
    cout << d << endl;

    cout << "Calling doNothing\n";
    doNothing(d2);
    cout << "Back from doNothing\n";

    Directory d3;
    d3 = d2;

    // Should display 1592
    cout << d2["Carmack"] << endl;

    // Should display error message
    cout << d2["Jeff"] << endl;

} // main
