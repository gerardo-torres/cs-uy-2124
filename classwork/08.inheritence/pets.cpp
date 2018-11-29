#include <iostream>
#include <vector>
using namespace std;
class Pet{
public:
    Pet (const string &name) : name(name) {}
    // Polymorphism  - allow each one to eat in its
    // own way
    virtual void eat() const {
        cout << "am eating\n";
    }
    virtual ~Pet() {}
private:
    string name;
};

class Cat : public Pet {
public:
    Cat (const string &name) : Pet(name) {};
    void purr() const {
        cout << "am purring\n";
    }
    void eat() const {
        cout << "cat eating\n";
    }
private:
    string name;
};

class Snail : public Pet {
public:
    Snail (const string &name) : Pet(name) {}
private:
    string name;
};

class Roach : public Pet {
public:
    using Pet::Pet; // Receive constructors from the base class
    // Roach(const string &name) : Pet(name) {}
private:
    string name;
};

// Pass by referece to avoid "slicing problem"
// And allow polymorphirm to occur
void silly(const Pet& currPet) {
    currPet.eat();
}

void silly2(const Cat& currCat) {
    currCat.purr();
}

int main() {
    Cat felix("felix");
    Pet peeve("peeve");
    silly2(felix);
    
    Snail gary("gary");
    peeve = gary;
    // gary = peeve;        // Not allowed to do this

    Pet* petPtr;
    Snail* snailPtr = &gary;
    Cat* catPtr = &felix;

    petPtr = catPtr;
    petPtr->eat();          // Can eat like a Cat
    // petPtr->purr();      // Pointer is still a type Pet
    // catPtr = petPtr;     // Cannot assign base to derived
    catPtr->purr();

    Roach archie("archie");
    vector<Pet*> myPets;
    myPets.push_back(&gary);
    myPets.push_back(&peeve);
    myPets.push_back(&felix);
    for (size_t i = 0; i < myPets.size(); ++i) {
        myPets[i]->eat();
    }
}
