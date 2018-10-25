#include <iostream>
using namespace std;
class Pet{
public:
    void eat() const {
        cout << "am eating\n";
    }
private:
};

class Cat : public Pet {};
class Snail : public Pet {};
class Roash : public Pet {};

void silly(Pet& currPet) {
    currPet.eat();
}

int main() {
    Cat felix;
    felix.eat();
    Pet peeve;
    silly(felix);
    silly(peeve);
}
