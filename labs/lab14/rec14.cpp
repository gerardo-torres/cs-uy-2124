/*
Author:         Gerardo Torres
Class:          CS-UY 2124
File Name:      rec14.cpp
-------------------------------------------------------------
Description:    Tasks on recursion
-------------------------------------------------------------
compile:        $ g++ rec14.cpp -o rec14
run:            $ ./rec14
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <string>
#include <exception>
#include <stdexcept>

//#define NDEBUG
#include <cassert>

using namespace std;

// Data structure Nodes ----------------------

// List Node
struct Node {
    Node(int data = 0, Node* next = nullptr) 
    : data(data), next(next) {}
    int data;
    Node* next;
};

// Tree Node
struct TNode {
  TNode(int data = 0, TNode *left = nullptr, TNode *right = nullptr)
    : data(data), left(left), right(right) {}
  int data;
  TNode *left, *right;
};


// Task Solutions ----------------------------

// Task One
bool evenOnes(int num) {
    if (num == 0) return true;
    if (num == 1) return false;
    if (num % 2 == 0) {
        return evenOnes(num / 2);
    } else {
        return !evenOnes(num / 2);
    }
}

// Task Two
Node* sumLists(Node* lo, Node* hi) {
    int sum = 0;
    if (lo != nullptr) sum += lo->data;
    if (hi != nullptr) sum += hi->data;
    Node* temp = nullptr;
    if (lo != nullptr && hi != nullptr) {
        temp = sumLists(lo->next, hi->next);
    }
    Node* curr = new Node(sum, temp);
    return curr;
}

// Task Three
int maxValueBTree(TNode* root) {
    if (root == nullptr) {
        throw invalid_argument("wrong!");
    }
    int curr = root->data;
    int left = INT_MIN;
    int right = INT_MIN;
    int currLargest = left;
    if (root->left != nullptr) {
        left = maxValueBTree(root->left);
    }
    if (root->right != nullptr) {
        right = maxValueBTree(root->right);
    }
    if (right > currLargest) currLargest = right;
    if (curr > currLargest) currLargest = curr;
    return currLargest;
}

// Task Four
bool palindrome(char arr[], int size) {
    if (size <= 1) return true;
    if (*arr == arr[size - 1]) {
        return palindrome(++arr, size-2);
    } else {
        return false;
    }
}

// Task Five
int towers(int num, char start, char target, char spare) {
    if (num == 1) return 1;
    return towers(num - 1, start, spare, target) + \
     towers(num - 1, spare, target, start) + 1;
}

// Testing the tasks ----------------------------

void displayList(Node* head) {
    Node* curr = head;
    while (curr != nullptr) {
        cout << curr->data;
        cout << " -> ";
        if (curr->next == nullptr) {
            cout << "null\n";
        }
        curr = curr->next;   
    }
}

void taskOne() {
    cout << "\ntaskOne()\n=========\n";
    cout << evenOnes(5) << '\n';
}

void taskTwo() {
    cout << "\ntaskTwo()\n=========\n";
    Node* c = new Node(6, nullptr);
    Node* b = new Node(1, c);
    Node* a = new Node(3, b);
    Node* z = new Node(2, nullptr);
    Node* y = new Node(4, z);
    displayList(a);
    displayList(y);
    cout << "sumLists(a, y)\n";
    Node* r = sumLists(a, y);
    displayList(r);
}

/*

           32
        /      \
      8         16
    /   \      /
   1     2    4 

*/

void taskThree() {
    cout << "\ntaskThree()\n=========\n";
    TNode a(1), b(2), c(4), d(8, &a, &b), e(16, &c), f(32, &d, &e);
    cout << maxValueBTree(&f) << endl;
    // TNode empty = nullptr;
}

void taskFour() {
    cout << "\ntaskFour()\n=========\n";
    char s[] = "racecar";
    cout << s<< "\n";
    // if (palindrome(s, 7)) { 
    //     cout << "Yes!\n"; 
    // } else {
    //     cout << "No!\n";
    // }
}

void taskFive() {
    cout << "\ntaskFive()\n=========\n";
    cout << towers(1, 'a', 'b', 'c') << "\n";       // 1 
    cout << towers(2, 'a', 'b', 'c') << "\n";       // 3
    cout << towers(3, 'a', 'b', 'c') << "\n";       // 7
    cout << towers(4, 'a', 'b', 'c') << "\n";       // 15
    cout << towers(5, 'a', 'b', 'c') << "\n";       // 31
    cout << towers(6, 'a', 'b', 'c') << "\n";       // 63
    cout << towers(7, 'a', 'b', 'c') << "\n";       // 127
    cout << towers(8, 'a', 'b', 'c') << "\n";       // 255
    cout << towers(9, 'a', 'b', 'c') << "\n";       // 511
    cout << towers(10, 'a', 'b', 'c') << "\n";      // 1023
}

int main() {
    cout << boolalpha;
    // taskOne();
    // taskTwo();
    // taskThree();
    taskFour();
    // taskFive();
}
