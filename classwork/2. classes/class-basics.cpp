#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// const methods
class Vorlon {
  public:
    Vorlon(const string &aName) : myName(aName) {}
    void display() const { cout << "Displaying a Vorlon named " << myName << endl; } // Finally, we did it right!!!
  private:
    string myName;
};

class Cat {
public:
   Cat(const string& theName, const string& theColor, double theWeight) 
      : name(theName), weight(theWeight), color(theColor) { }
   void display() const {
      cout << "Displaying a Cat named" << name << " with color " << color << " and weight " << weight << endl;
   }
private:
   string name;
   string color;
   double weight;
};

// vector of objects
void fillCatVector (ifstream& ifs, vector<Cat>& vc) {
    string name;   // Used to read in the name
    string color;  // Used to read in the color
    double weight; // Used to read in the weight
    while (ifs >> name >> color >> weight) {
      Cat aCat(name, color, weight);  // Cat object defined inside loop.
      vc.push_back(aCat);
   }
}

class Vorlon {
public:
    Vorlon(const string& aName);
    void display() const;  // const is part of the prototype.
private:
    string myName;
};

Vorlon::Vorlon(const string& aName) : myName(aName) {} 
void Vorlon::display() const {
    cout << "Displaying a Vorlon named " << myName << endl;
}

int main() {
    Vorlon v("Kosh");
    v.display();
}

