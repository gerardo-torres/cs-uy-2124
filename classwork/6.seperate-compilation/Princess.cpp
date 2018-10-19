#include "Princess.h"
#include "FrogPrince.h"
#include <string>
#include <iostream>
using namespace std;

namespace Fantasy {

    void Princess::marries(FrogPrince& betrothed) {
        spouse = &betrothed;
        betrothed.setSpouse(this);
    }

    void Princess::display() const { 
        cout << "Princess: " << name << endl;
    }

    Princess::Princess(const string& name) : name(name) {}

}
