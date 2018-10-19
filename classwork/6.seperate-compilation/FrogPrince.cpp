#include "FrogPrince.h"
#include "Princess.h"
#include <string>
#include <iostream>
using namespace std;

namespace Fantasy {

    // FrogPrince implementation code
    FrogPrince::FrogPrince(const string& name) : name(name) {}
    void FrogPrince::display() const { cout << "Frog: " << name << endl;}
    void FrogPrince::setSpouse(Princess* pp) {
        spouse = pp;
    }

}
