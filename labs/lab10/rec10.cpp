/*
Author:         Gerardo Torres
Class:          CS-UY 2124
File Name:      rec10.cpp
-------------------------------------------------------------
Description:    Inheritence using classes of instruments
-------------------------------------------------------------
compile:        $ g++ rec10.cpp -o rec10
run:            $ ./rec10
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Instrument {
public:
    Instrument() {}
    
    virtual void makeSound() const = 0;
    
    virtual void play() const = 0;
private:
};

void Instrument::makeSound() const {
    cout << "To make a sound...";
}

// Brass instruments --------------------------------------
class Brass : public Instrument {
public:
    Brass(unsigned newSize)
    : size(newSize) {}
    
    void makeSound() const {
        Instrument::makeSound();
        cout << " blow on a mouthpiece of size " << size << '\n';
    }
    
    virtual void play() const {};
private:
    unsigned size;
};

class Trombone : public Brass {
public:
    Trombone(unsigned newSize)
    : Brass(newSize) {}

    void play() const { cout << "Blat"; }
};

class Trumpet : public Brass {
public:
    Trumpet(unsigned newSize)
    : Brass(newSize) {}

    void play() const { cout << "Toot"; }
private:
};

// String instruments --------------------------------------
class String : public Instrument {
public:
    String(unsigned newPitch)
    : pitch(newPitch) {}
    
    void makeSound() const {
        Instrument::makeSound();
        cout << " bow a string with pitch " << pitch << '\n';
    }
    
    virtual void play() const {};

private:
    unsigned pitch;
};

class Violin : public String {
public:
    Violin(unsigned newPitch)
    : String(newPitch) {}

    void play() const { cout << "Screech"; }
private:
};

class Cello : public String {
public:
    Cello(unsigned newPitch) 
    : String(newPitch) {}

    void play() const { cout << "Squawk"; }
private:
};

// Percussion instruments --------------------------------------
class Percussion : public Instrument {
public:
    Percussion() {}
    
    void makeSound() const {
        Instrument::makeSound();
        cout << " hit me\n";
    }
    
    virtual void play() const {};
};

class Drum : public Percussion {
public:
    Drum()
    : Percussion::Percussion() {}

    void play() const { cout << "Boom"; }
};

class Cymbal : public Percussion {
public:
    Cymbal()
    : Percussion::Percussion() {}

    void play() const { cout << "Crash"; }
};

// Musician ----------------------------------------------------
class Musician {
public:
    Musician() : instr(nullptr) {}

    void acceptInstr(Instrument* instPtr) { instr = instPtr; }

    Instrument* giveBackInstr() { 
        Instrument* result(instr); 
        instr = nullptr;
        return result;
    }

    void testPlay() const {
        if (instr) instr->makeSound(); 
        else cerr << "have no instr\n";
    }

    void play() const {
        if (instr) instr->play(); 
    }

private:
    Instrument* instr;
};

// Musical Instrument Lending Library ---------------------------
class MILL {
public:
    MILL() : currSize(0) {}

    void dailyTestPlay() {
        for (Instrument* currInstrument : instruments) {
            if (currInstrument) { currInstrument->makeSound(); }
        }
    }

    void receiveInstr(Instrument& newInstrument) {
        Instrument* instruPtr = &newInstrument;
        if (currSize == instruments.size()) {
            instruments.push_back(instruPtr);
            ++currSize;
        } 
        for (size_t i = 0; i < instruments.size(); ++i) {
            Instrument *currBin = instruments[i];
            if (currBin == nullptr) {
                instruments[i] = instruPtr;
                ++currSize;
                return;
            }
        }
    }

    Instrument* loanOut() {
        if (currSize == 0) { return nullptr; }
        for (size_t i = 0; i < instruments.size(); ++i) {
            Instrument* currBin = instruments[i];
            if (currBin != nullptr) {
                --currSize;
                instruments[i] = nullptr;
                return currBin;
            }
        }
    }
private:
    vector<Instrument*> instruments;
    int currSize;
};

class Orch {
public:
    void addPlayer(Musician& newPlayer) {
        if (musicians.size() == 25) {cerr << "could not add musician\n";}
        else musicians.push_back(&newPlayer);
    }
    void play() const {
        for (Musician* currMusician : musicians) {
            currMusician->play();
        }
        cout << '\n';
    }
private:
    vector<Musician*> musicians;
};

// PART ONE
int main1() {
    cout << "Define some instruments ----------------------------------------\n";
    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12) ;
    Violin violin(567) ;
  
    // use the debugger to look at the mill
    cout << "Define the MILL ------------------------------------------------\n";
    MILL mill;
  
    cout << "Put the instruments into the MILL ------------------------------\n";
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);
  
    cout << "Daily test -----------------------------------------------------\n";
    cout << endl;
    // cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;
  
    cout << "Define some Musicians-------------------------------------------\n";
    Musician harpo;
    Musician groucho;
  	
    cout << "TESTING: groucho.acceptInstr(mill.loanOut());-----------------------\n";
    groucho.testPlay();	
    cout << endl;
    groucho.acceptInstr(mill.loanOut());
    cout << endl;
    groucho.testPlay();
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
  
    cout << endl << endl;
  
    groucho.testPlay();	
    cout << endl;
    mill.receiveInstr(*groucho.giveBackInstr());
    harpo.acceptInstr(mill.loanOut());
    groucho.acceptInstr(mill.loanOut());
    cout << endl;
    groucho.testPlay();
    cout << endl;
    harpo.testPlay();
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
  
    cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ----------\n";
  
    // fifth
    mill.receiveInstr(*groucho.giveBackInstr());
    cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
    mill.receiveInstr(*harpo.giveBackInstr());

  
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;
  
    cout << endl;


}

// PART TWO
// The initialization phase
int main2() {
    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12);
    Violin violin(567);

    MILL mill;
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);

    Musician bob;
    Musician sue;
    Musician mary;
    Musician ralph;
    Musician jody;
    Musician morgan;

    Orch orch;

    // // THE SCENARIO

    //Bob joins the orchestra without an instrument.
    orch.addPlayer(bob);

    //The orchestra performs
    cout << "orch performs\n";
    orch.play();

    //Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.acceptInstr(mill.loanOut());
    orch.addPlayer(sue);
    cout << "orch performs\n";
    orch.play();

    //Ralph gets an instrument from the MIL2.
    ralph.acceptInstr(mill.loanOut());

    //Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.acceptInstr(mill.loanOut());
    orch.addPlayer(mary);

    //Ralph returns his instrument to the MIL2.
    mill.receiveInstr(*ralph.giveBackInstr());

    //Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.acceptInstr(mill.loanOut());
    orch.addPlayer(jody);

    // morgan gets an instrument from the MIL2
    morgan.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Ralph joins the orchestra.
    orch.addPlayer(ralph);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();
	
    // bob gets an instrument from the MIL2
    bob.acceptInstr(mill.loanOut());

    // ralph gets an instrument from the MIL2
    ralph.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Morgan joins the orchestra.
    orch.addPlayer(morgan);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

} // main

int main() {
    main1();
    main2();
}