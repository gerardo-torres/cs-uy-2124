/*
    testPrincess.cpp
    Cyclic Association
    Sec F
*/

#include <iostream>
#include <string>
using namespace std;

class FrogPrince;

class Princess {
public:
    Princess(const string& name);
    //Princess(const string& name) : name(name) {}

    void display() const;
    //void display() const { cout << "Princess: " << name << endl;}

    void marries(FrogPrince& betrothed);
    // void marries(FrogPrince& betrothed) {
    //     spouse = &betrothed;
    //     //betrothed.spouse = this;
    //     betrothed.setSpouse(this);
    // }
private:
    string name;
    FrogPrince* spouse;
};

class FrogPrince {
public:
    FrogPrince(const string& name);
    void display() const;
    void marries(Princess& betrothed);
    void setSpouse(Princess* bp);
private:
    string name;
    Princess* spouse;
};

int main() {
    Princess snowy("Snow White");
    snowy.display();
    FrogPrince froggy("Froggy");
    froggy.display();
    snowy.marries(froggy);
    snowy.display();
}


void Princess::marries(FrogPrince& betrothed) {
    spouse = &betrothed;
    //betrothed.spouse = this;
    betrothed.setSpouse(this);
}

void Princess::display() const { cout << "Princess: " << name << endl;}

Princess::Princess(const string& name) : name(name) {}


// FP
FrogPrince::FrogPrince(const string& name) : name(name) {}
void FrogPrince::display() const { cout << "Frog: " << name << endl;}
void FrogPrince::marries(Princess& betrothed) {
}
void FrogPrince::setSpouse(Princess* bp) {
    spouse = bp;
}
