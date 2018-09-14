/*
Author: Gerardo Torres
Class: CS-UY 2124
File Name: rec02.cpp
Description: takes a text file of Hydrocarbons and sorts them into a 
table based on their chemical formulas
compile: `$ g++ rec02.cpp -o rec02`
run: `$ ./rec02`
*/

#include <string>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

struct Hydrocarbon {
    string chemicalName;
    vector<string> vectorOfNames;
    int numberOfC;
    int numberOfH;
};

// returns
int findFormulaIndex(int numOfC, int numOfH, vector<Hydrocarbon> &vHydrocarbs)
{
    for (size_t i; i < vHydrocarbs.size(); ++i) {
        cout << vHydrocarbs[i].numberOfC << endl;
        int numC = vHydrocarbs[i].numberOfC;
        int numH = vHydrocarbs[i].numberOfH;
        if ((numC == numOfC) && (numH == numOfH))
        {
            vHydrocarbs[i].vectorOfNames.push_back(currFormula.chemicalName);
        }
    }

}

// takes the stream and inserts forumlas into vector as Formula structures
void readIntoVector(ifstream &ifs, vector<Hydrocarbon> &vHydrocarbs)
{
    Hydrocarbon currFormula;
    char carbon, hydrogen;
    int numOfC, numOfH;
    while (ifs >> currFormula.chemicalName >> carbon >> numOfC >> hydrogen >> numOfH) {
        findFormulaIndex(numOfC, numOfH, vHydrocarbs);
    }
    for (size_t i; i < vHydrocarbs.size(); ++i) {
        cout << vHydrocarbs[i].chemicalName << " c" << vHydrocarbs[i].numberOfC 
        << " h" << vHydrocarbs[i].numberOfH << endl;
    }
}

// asks user for filename and returns ifstream object ifs
ifstream askForFilename() {
    string fileName;
    cout << "Please enter a file name" << endl;
    cin >> fileName;
    ifstream ifs(fileName);
    while (!ifs) {
        cout << "Filename is invalid please try again" << endl;
        cin >> fileName;
        ifs.clear();
        ifs.open(fileName);
    }
    return ifs;
}

// bubblesort implementation to sort vector of strings in-place
void bubbleSort(vector<string> vectorOfNames) {
    int i;
    int j;
    int length = vectorOfNames.size();
    for (i = 0; i < length - 1; i++) {
        for (j = 0; length - i - 1; j++) {
            if (vectorOfNames[j] > vectorOfNames[j + 1]) {
                // vectorOfNames[j], vectorOfNames[j + 1] = vectorOfNames[j + 1], vectorOfNames[j];
                // swap(&vectorOfNames[j], &vectorOfNames[j + 1]);
            }
        }
    }
}

int main() {
    vector<Hydrocarbon> vHydroCarbs;
    ifstream ifs = askForFilename();
    readIntoVector(ifs, vHydroCarbs);
}