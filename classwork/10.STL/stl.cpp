/*
  The STL. Standard Template Library
  Sec 
*/

#include <vector>
#include <iostream> 
#include <list>
#include <algorithm>
using namespace std;

void print(char* start, char* stop) {  
    for (char* p = start; p != stop; ++p) {
        cout << *p << ' ';
    }
    cout << endl;
}

// void print(list::iterator start, list::iterator stop) {  
//     for (list::iterator p = start; p != stop; ++p) {
//         cout << *p << ' ';
//     }
//     cout << endl;
// }

template <class T>
void print(T start, T stop) {  
    for (T p = start; p != stop; ++p) {
        cout << *p << ' ';
    }
    cout << endl;
}

int main() {

  char array[] = "Bjarne Stroustrup";
  int len = 17;
  sort(array, array+len);

  vector<char> vc(array, array+len);

  list<char> lc(array, array+len);
  //list<char> lc2(vc);  // not in the stl
  list<char> lc2(vc.begin(), vc.end()); 

  for (char* p = array; p != array+len; ++p) {
      cout << *p << ' ';
  }
  cout << endl;
  print(array, array+len);
  print(lc.begin(), lc.end());
}


