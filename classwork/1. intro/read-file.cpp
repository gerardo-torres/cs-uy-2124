#include <iostream> // cin, cout, cerr, endl
#include <fstream>  // ifstream
#include <string>   // string

using namespace std;

int main() {
    ifstream ifs;
    string fileName;
    cout << "What is the name of the file? ";
    cin >> fileName;
    ifs.open(fileName);
    if (!ifs) {
        cerr << "Cloudn't open " << fileName << '\n';
    }
    string name;
    while (ifs >> name) {
        cout << name << '\n';
    }
    ifs.close();
}
