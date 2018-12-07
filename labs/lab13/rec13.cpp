/*
Author:         Gerardo Torres
Class:          CS-UY 2124
File Name:      rec13.cpp
-------------------------------------------------------------
Description:    STL tutorial
-------------------------------------------------------------
compile:        $ g++ rec13.cpp -o rec13
run:            $ ./rec13
*/
#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23
using namespace std;

// Task 16
class IsEven {
    public:
        bool operator() (int n) const {
            return n % 2 == 0;
        }
};


// Task 9
void printList(const list<int>& lst) {
    list<int>::const_iterator iter = lst.begin();
    while (iter != lst.end()) {
        cout << *iter << ' ';
        iter++;
    }
    cout << '\n';
}

// Task 10
void printList2(const list<int>& lst) {
    for (int curr : lst) {
        cout << curr << ' ';
    }
    cout << '\n';
}

// Task 11
void printListAuto(const list<int>& lst) {
    auto iter = lst.begin();
    while (iter != lst.end()) {
        cout << *iter << ' ';
        ++iter;
        if (iter != lst.end()) {
            ++iter;
        }
    }
    cout << '\n';
}

// Task 12
list<int>::const_iterator findItem(const list<int>& lst, int data) {
    list<int>::const_iterator iter = lst.begin();
    while (iter != lst.end()) {
        if (*iter == data) {
            return iter;
        }
        ++iter;
    }
    return lst.end();
}

// Task 13
auto findItem2(const list<int>& lst, int data) {
    auto iter = lst.begin();
    while (iter != lst.end()) {
        if (*iter == data) return iter;
        ++iter;
    }
    return lst.end();
}

// Task 15
bool isEven(int x) {
    return x % 2 == 0;
}

// Task 19
list<int>::const_iterator ourFind(list<int>::const_iterator start, list<int>::const_iterator end, int target) {
    list<int>::const_iterator curr = start;
    while (curr != end) {
        if (*curr == target) {
            return curr;
        }
        ++curr;
    }
    return end;
}

// Task 20
template <typename T>
T ourFind(T start, T end, int target) {
    cout << "am in the template ourFind() function\n";
    T curr = start;
    while (curr != end) {
        if (*curr == target) {
            return curr;
        }
        ++curr;
    }
    return end;
}

bool wordExists(vector<string> unique, string& word) {
    for (string curr : unique) {
        if (curr == word) {
            return true;
        }
    }
    return false;
}

// Task 21
void distinctWords() {
    ifstream ifs;
    string word;
    vector<string> unique;
    ifs.open("file.txt");
    while (ifs >> word) {
        if (! wordExists(unique, word)) {
            unique.push_back(word);
        }
    }
    ifs.close();
    cout << unique.size() << '\n';
}

void distinctWordsSet() {
    ifstream ifs;
    string word;
    set<string> unique;
    ifs.open("file.txt");
    while (ifs >> word) {
        unique.insert(word);
    }
    ifs.close();
    cout << unique.size() << '\n';
}

void myWordMap() {
    ifstream ifs;
    string word;
    map<string, vector<int>> wordMap;
    ifs.open("file.txt");
    int i = 0;
    while (ifs >> word) {
        wordMap[word].push_back(i);
        ++i;
    }
    ifs.close();
    for (auto pair : wordMap) {
        cout << pair.first << "->";
        for (int num : pair.second) {
            cout << num << " ";
        } 
        cout << '\n';
    }
    cout<<wordMap.size();

}

int main() {
    // 1. Create a vector with some values and display using ranged for
    cout << "Task 1:\n";
    vector<int> vec({3, 5, 1, 4, 2});
    for (int curr : vec) {
        cout << curr << " ";
    }
    cout << '\n';
    cout << "\n=======\n";

    // 2. Initalize a list as a copy of values from the vector
    cout << "Task 2:\n";
    // list<int> lst(vec);
    list<int> lst({3, 5, 1, 4, 2});
    for (int curr : lst) {
        cout << curr << " ";
    }
    cout << '\n';
    cout << "\n=======\n";

    // 3. Sort the original vector.  Display both the vector and the list
    cout << "Task 3:\n";
    std::sort(vec.begin(), vec.end());
    for (int curr : vec) {
        cout << curr << " ";
    }
    cout << '\n';
    for (int curr : lst) {
        cout << curr << " ";
    }
    cout << '\n';
    cout << "\n=======\n";

    // 4. print every other element of the vector.
    cout << "Task 4:\n";
    for (size_t i = 0; i < vec.size(); ++i) {
        if (i % 2 == 0) {
            cout << vec[i] << " ";
        }
    }
    cout << '\n';

    cout << "\n=======\n";

    // 5. Attempt to print every other element of the list using the
    //    same technique.
    cout << "Task 5:\n";
    // for (size_t i = 0; i < lst.size(); ++i) {
    //     curr = lst[i];       // doesn't compile
    //     if (i % 2 == 0) {
    //         cout << curr << " ";
    //     }
    // }
    cout << "it is not supposed to compile\n";


    cout << "\n=======\n";

    //
    // Iterators
    //

    // 6. Repeat task 4 using iterators.  Do not use auto;
    cout << "Task 6:\n";
    vector<int>::iterator iter = vec.begin();
    while(iter < vec.end()) {
        cout << *iter << ' ';
        iter = iter + 2;
    }
    cout << '\n';

    cout << "\n=======\n";

    // 7. Repeat the previous task using the list.  Again, do not use auto.
    //    Note that you cannot use the same simple mechanism to bump
    //    the iterator as in task 6.
    cout << "Task 7:\n";
    list<int>::iterator lstIter = lst.begin();
    while(lstIter != lst.end()) {
        cout << *lstIter << ' ';
        lstIter++;
        if (lstIter != lst.end()) {
            lstIter++;
        }
    }
    cout << '\n';

    cout << "\n=======\n";

    // 8. Sorting a list
    cout << "Task 8:\n";
    lst.sort();
    for (int curr : lst) {
        cout << curr << " ";
    }
    cout << '\n';

    cout << "\n=======\n";

    // 9. Calling the function to print the list
    cout << "Task 9:\n";
    printList(lst);

    cout << "=======\n";

    // 10. Calling the function that prints the list, using ranged-for
    cout << "Task 10:\n";
    printList2(lst);

    cout << "=======\n";

    //
    // Auto
    //

    // 11. Calling the function that, using auto, prints alterate
    // items in the list
    cout << "Task 11:\n";
    printListAuto(lst);


    cout << "=======\n";

    
    // 12.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 12:\n";
    list<int>::const_iterator four = findItem(lst, 4);
    list<int>::const_iterator ten = findItem(lst, 10);
    cout << *four << '\n';
    cout << *ten << '\n';

    cout << "=======\n";

    // 13.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 13:\n";
    auto four2 = findItem2(lst, 4);
    auto ten2 = findItem2(lst, 10);
    cout << *four2 << '\n';
    cout << *ten2 << '\n';

    cout << "=======\n";

    //
    // Generic Algorithms
    //

    // 14. Generic algorithms: find
    cout << "Task 14:\n";
    auto three = find(lst.begin(), lst.begin(), 5);
    printList(lst);
    cout << *three << '\n';

    cout << "=======\n";

    // 15. Generic algorithms: find_if
    cout << "Task 15:\n";
    auto firstEven = find_if(lst.begin(), lst.end(), isEven);
    cout << *firstEven << '\n';

    cout << "=======\n";

    // 16. Functor
    cout << "Task 16:\n";
    auto firstEven2 = find_if(lst.begin(), lst.end(), IsEven());

    cout << "=======\n";
    
    // 17. Lambda
    cout << "Task 17:\n";
    auto firstEven3 = find_if(lst.begin(), lst.end(), [] (int curr) { return curr % 2 == 0; });
    cout << *firstEven3 << '\n';
    cout << "=======\n";

    // 18. Generic algorithms: copy to an array
    cout << "Task 18:\n";
    int arr[5];
    copy(lst.begin(), lst.end(), arr);

    int* firstEvenArr = find_if(arr, arr + 5, [] (int curr) { return curr % 2 == 0; } );
    cout << *firstEvenArr << '\n';

    cout << "=======\n";

    //
    // Templated Functions
    //

    // 19. Implement find as a function for lists
    cout << "Task 19:\n";
    auto ans = ourFind(lst.begin(), lst.end(), 2);
    cout << *ans << '\n';


    cout << "=======\n";
    
    // 20. Implement find as a templated function
    cout << "Task 20:\n";
    auto ans2 =  ourFind(lst.begin(), lst.end(), 2);
    cout << *ans2 << '\n';

    cout << "=======\n";

    //
    // Associative collections
    //

    // 21. Using a vector of strings, print a line showing the number
    //     of distinct words and the words themselves.
    cout << "Task 21:\n";
    distinctWords();

    cout << "\n=======\n";

    // 22. Repeating previous step, but using the set
    cout << "Task 22:\n";
    distinctWordsSet();
    

    cout << "=======\n";

    // 23. Word co-occurence using map
    cout << "Task 23:\n";
    myWordMap();


    cout << "=======\n";
}
