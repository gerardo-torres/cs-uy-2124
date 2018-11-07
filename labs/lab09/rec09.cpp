/*
Author:         Gerardo Torres
Class:          CS-UY 2124
File Name:      rec09.cpp
-------------------------------------------------------------
Description:    Introduction to inheritence
-------------------------------------------------------------
compile:        $ g++ rec09.cpp -o rec09
run:            $ ./rec09
*/

#include <iostream>
#include <vector>
using namespace std;


/*                    UML

                Printed Material
                /              \
              Book           Magazine
           /       \
       Textbook   Novel

*/

class PrintedMaterial {
public:
    PrintedMaterial(unsigned numberOfPages)
    : numberOfPages(numberOfPages) {}
    
    // The addition of the virtual keyword 
    virtual void displayNumberOfPages() const = 0;

    // virtual void testMethod() const = 0;        // correct
    // virtual void testMethod() const = 0 {}   // incorrect

  protected:
  private:
    unsigned numberOfPages;
};

void PrintedMaterial::displayNumberOfPages() const {
    cout << numberOfPages << '\n';
}

class Magazine : public PrintedMaterial {
public:
    Magazine(unsigned numberOfPages)
    : PrintedMaterial(numberOfPages) {}

    void displayNumberOfPages() const {
        PrintedMaterial::displayNumberOfPages();
    }

protected:

private:
    // unsigned numberOfPages; // Incorrect
};

class Book : public PrintedMaterial {
public:
    Book(unsigned numberOfPages)
    : PrintedMaterial(numberOfPages) {}

protected:

private:
    // unsigned numberOfPages; // Incorrect
};

class TextBook : public Book {
public:
    TextBook(unsigned numberOfPages, unsigned numIndex)
    : Book(numberOfPages), numIndex(numIndex) {}

    void displayNumberOfPages() const {
        cout << "total pages: ";
        PrintedMaterial::displayNumberOfPages();
        cout << "index pages: " << numIndex << '\n';
    }

protected:

private:
    // unsigned numberOfPages; // Incorrect
    unsigned numIndex;
};

class Novel : public Book {
public:
    Novel(unsigned numberOfPages)
    : Book(numberOfPages) {}

    void displayNumberOfPages() const {
        PrintedMaterial::displayNumberOfPages();
    }
protected:

private:
    // unsigned numberOfPages; // Incorrect
};

void displayNumberOfPages(const PrintedMaterial& anyPM) {
    anyPM.displayNumberOfPages();
}

// tester/modeler code
int main() {
	TextBook t(3500, 100);
	Novel n(100);
	Magazine m(30);
    
    // t.displayNumberOfPages();
    // PrintedMaterial pm = t;  // like putting a t into a vector of PrintedMaterials
    // pm.displayNumPages();    // Slicing problem!
    
    PrintedMaterial* ptrPM;
    ptrPM = &t;
    ptrPM->displayNumberOfPages();

    // t.displayNumberOfPages();
    n.displayNumberOfPages();
    m.displayNumberOfPages();

    cout << "general function...\n";

    displayNumberOfPages(t);
    displayNumberOfPages(n);
    displayNumberOfPages(m);

    cout << "pushing all the PMs into a vector\n\n";
    vector<PrintedMaterial*> allPMs;
    allPMs.push_back(&t);
    allPMs.push_back(&n);
    allPMs.push_back(&m);
    
    for (PrintedMaterial* currPM: allPMs) {
        currPM->displayNumberOfPages();
    }

}
