/*
Author: Gerardo Torres
Class: CS-UY 2124
File Name: rec02.cpp

Description: takes a text file of Hydrocarbons and sorts 
them into a table based on their Carbon count

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
    int numberOfC;
    int numberOfH;
    vector<string> vNames;
};

// returns whether hydrocarbon exists in the vector
bool hcExists(vector<Hydrocarbon> &vHydroCarbs, int numOfC, int numOfH) {
    int length = vHydroCarbs.size();
    for (size_t i = 0; i < length; ++i) {
        Hydrocarbon currHC = vHydroCarbs[i];
        if ((currHC.numberOfC == numOfC) && (currHC.numberOfH == numOfH)) {
            return true;
        }
    }
    return false;
}

// returns index of where to place
int findHydroCarbIndex(vector<Hydrocarbon> &vHydroCarbs, int numOfC, int numOfH) {
    int length = vHydroCarbs.size();
    for (size_t i = 0; i < length; ++ i) {
        Hydrocarbon currHC = vHydroCarbs[i];
        if ((currHC.numberOfC == numOfC) && (currHC.numberOfH == numOfH)) {
            return i;
        }
    }
}

// takes the stream and inserts forumlas into vector as Formula structures
void readIntoVector(ifstream &ifs, vector<Hydrocarbon> &vHydroCarbs) {
    char carbon, hydrogen;
    int numOfC, numOfH;
    string name;
    while (ifs >> name >> carbon >> numOfC >> hydrogen >> numOfH) {
        Hydrocarbon currHydroCarb;
        if (hcExists(vHydroCarbs, numOfC, numOfH)) {
            // current hydrocarbon config exists; find at which index to insert
            int insertIndex = findHydroCarbIndex(vHydroCarbs, numOfC, numOfH);
            Hydrocarbon indexedHydroCarb = vHydroCarbs[insertIndex];
            vHydroCarbs[insertIndex].vNames.push_back(name);
        } else {
            // current hydrocarbon config does not exist; create a new one
            currHydroCarb.numberOfC = numOfC;
            currHydroCarb.numberOfH = numOfH;
            currHydroCarb.vNames.push_back(name);
            vHydroCarbs.push_back(currHydroCarb);
        }
    }
}

// asks user for filename and returns ifstream object ifs
void askForFilename(ifstream &ifs) {
    string fileName;
    cout << "Please enter a file name\n";
    cin >> fileName;
    ifs.open(fileName);
    while (!ifs) {
        ifs.clear();
        cout << "Filename is invalid please try again\n";
        cin >> fileName;
        ifs.open(fileName);
    }
}

void swap(vector<Hydrocarbon> &vHydroCarbs, int j) {
    Hydrocarbon temp = vHydroCarbs[j];
    vHydroCarbs[j] = vHydroCarbs[j + 1];
    vHydroCarbs[j + 1] = temp;
}

// bubble sort implementation to sort hydrocarbons by carbon count in-place
void bubbleSort(vector<Hydrocarbon> &vHydroCarbs) {
    int i, j;
    int length = vHydroCarbs.size();
    // iterating through Hydrocarbon
    for (size_t i = 0; i < length; i++) {
        for (size_t j = 0; j < length - i - 1; j++) {
            if (vHydroCarbs[j].numberOfC > vHydroCarbs[j + 1].numberOfC) {
                // sorting by Carbons
                swap(vHydroCarbs, j);
            } else if (vHydroCarbs[j].numberOfC == vHydroCarbs[j + 1].numberOfC) {
                // if Carbons are equal, Hydrogen is the tiebreaker
                if (vHydroCarbs[j].numberOfH > vHydroCarbs[j + 1].numberOfH) {
                    swap(vHydroCarbs, j);
                }
            }
        }
    }
}

// display hydroarbons to the terminal
void displayHydrocarbons(vector<Hydrocarbon> &vHydroCarbs) {
    int lengthVector = vHydroCarbs.size();
    for (size_t i = 0; i < lengthVector; ++i) {
        Hydrocarbon currHC = vHydroCarbs[i];
        cout << 'C' << currHC.numberOfC << 'H' << currHC.numberOfH << " -> ";
        int lengthNames = currHC.vNames.size();
        for (size_t j = 0; j < lengthNames; ++j) {
            cout << currHC.vNames[j] << ", ";
        }
        cout << '\n'; // end of hydrocarbon object
    }
}

int main() {
    vector<Hydrocarbon> vHydroCarbs;
    ifstream ifs;
    askForFilename(ifs);
    readIntoVector(ifs, vHydroCarbs);
    bubbleSort(vHydroCarbs);
    displayHydrocarbons(vHydroCarbs);
}