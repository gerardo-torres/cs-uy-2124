/*
Author:         Gerardo Torres
Class:          CS-UY 2124
File Name:      midterm1.cpp
-----------------------------------------------------------
Description:    Studying for the first midterm!
-----------------------------------------------------------
compile:        $ g++ .midterm1.cpp -o midterm1
run:            $ ./midterm1
*/
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Person {
    friend ostream& operator<<(ostream& os, const Person& rhs) {
        // os << "Address: " << &rhs << '\n';
        Person* theirSpouse = rhs.getSpouse();
        os << "Name: " << rhs.name << "\nAge: " << rhs.age;
        os << "\nGender: " << rhs.gender << "\nSpouse: ";
        if (theirSpouse != nullptr) {
            os << theirSpouse->getName();
        } else {
            os << "None";
        }
        os << "\n\n";
        return os;
    }

public:
    // initializing name and gender
    Person(const string& aName, const string& aGender)
    : name(aName), gender(aGender), age(0), spouse(nullptr) {}

    // initializing name gender and age
    Person(const string& aName, const string& aGender, int anAge)
    : name(aName), gender(aGender), age(anAge), spouse(nullptr) {}

    int getAge() const {
        return age;
    }

    string getName() const {
        return name;
    }

    void increaseAge() {
        ++age;
    }

    Person* getSpouse() const {
        return spouse;
    }

    bool getMarried(Person& newSpouse) {
        // check for self-assignment
        if (&newSpouse != this && spouse == nullptr) {
            spouse = &newSpouse;
            newSpouse.spouse = this;
            return true;
        }
        return false;
    }

private:
    string name;
    string gender;
    Person* spouse;
    int age;
};

class DirectoryBrooklyn {
public:
    
    void add(Person& newResident) {
        Person* personPtr = &newResident;
        residents.push_back(personPtr);
    }

    int countMarried() const {
        int count = 0;
        for (Person* currPerson : residents) {
            if (currPerson->getSpouse() != nullptr) {
                ++count;
            }
        }
        return count;
    }

    size_t findResident(const string& residentName) {
        size_t i = 0;
        for (Person* currPerson : residents) {
            if (residentName == currPerson->getName()) {
                return i;
            }
            ++i;
        }
        return -1;
    }

private:
    vector<Person*> residents;
};

class DirectoryQueens {
public:
    
private:
    Person** residents;
};

void readFile(DirectoryQueens& queens) {

}

void classOperations() {
    DirectoryBrooklyn brooklyn;
    DirectoryQueens queens;
    Person jake("jake", "male");
    for (int i = 0; i < 28; ++i) {
        jake.increaseAge();
    }
    Person jane("jane", "female", 28);
    // cout << "before married:\n";
    // cout << jane << jake;
    jane.getMarried(jake);
    // cout << "after married:\n";
    cout << jane << jake;
    brooklyn.add(jane);
    brooklyn.add(jake);
    readFile(queens);
}

void pointers() {
    int x = 39;
    int* px = &x;
    cout << "x = " << x << '\n';
    cout << "&x = " << px << '\n';
    cout << "*px = " << *px << '\n';
    cout << "&px = " << &px << '\n';
}

int main() {
    // pointers();
    classOperations();

}