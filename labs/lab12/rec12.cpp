/*
Author:         Gerardo Torres
Class:          CS-UY 2124
File Name:      rec12.cpp
-------------------------------------------------------------
Description:    Implementing a Doubly Linked List. Focus on
                Packaging a data structure as a class,
                Iterators, and Copy control
-------------------------------------------------------------
compile:        $ g++ rec12.cpp -o rec12
run:            $ ./rec12
*/

#include <cstdlib>
#include <iostream>
using namespace std;

class List {

    class Node;

    friend ostream& operator<<(ostream& os, List& rhs) {
        Node* curr = rhs.head->next;
        for (int i = 0; i < rhs.listSize; ++i) {
            os << "\ndata:\t" << curr->data;
            os << "\nnode:\t" << curr;
            os << "\nprev:\t" << curr->prev;
            os << "\nnext:\t" << curr->next << '\n';
            curr = curr->next;
            cout << '\n';
        }
        return os;
    }

public:
    class Iterator {
        friend List; // Lets list access private
        friend  ostream& operator<<(ostream& os, Iterator& rhs) {
            os << "node:\t" << rhs.nodePtr;
            os << "\ndata:\t" << *rhs;
            os << "\n\n";
            return os;
        }

        friend bool operator==(const Iterator& lhs, const Iterator&rhs) {
            return lhs.nodePtr == rhs.nodePtr;
        }
        
        friend bool operator!=(const Iterator& lhs, const Iterator&rhs) {
            return lhs.nodePtr != rhs.nodePtr;
        }
    
    public:
        Iterator(Node* nodePtr = nullptr)
        : nodePtr(nodePtr) {}

        Iterator& operator++() {
            nodePtr = nodePtr->next;
            return *this;
        }

        int getData() const { return nodePtr->data; }

        Iterator& operator--() {
            nodePtr = nodePtr->prev;
            return *this;
        }

        int operator*() const { return nodePtr->data; }

        int& operator*() { return nodePtr->data; }

    private:
        Node* nodePtr;
    };

    List() 
        : listSize(0) {
            tail = new Node(0, nullptr, nullptr);
            head = new Node(0, nullptr, tail);
            tail->prev = head;
        }

    void printInfo() {
        cout << "head\t\t" << head <<'\n';
        cout << "head->next\t" << head->next << '\n';
        
        cout << "\ntail\t\t" << tail << '\n';
        cout << "tail->prev\t" << tail->prev << '\n';
    }

    void push_back(int data) {
        Node* left = tail->prev;
        Node* newNode = new Node(data, left, tail);
        left->next = newNode;
        tail->prev = newNode;
        listSize++;
    }
    
    void push_front(int data) {
        Node* right = head->next;
        Node* newNode = new Node(data, head, right);
        right->prev = newNode;
        head->next = newNode;
        listSize++;
    }

    int size() {
        return listSize;
    }

    void pop_back() {
        if (listSize > 0) {
            Node* newLast = tail->prev->prev;
            delete tail->prev;
            newLast->next = tail;
            tail->prev = newLast;
            listSize --;
        }
    }

    void pop_front() {
        if (listSize > 0) {
            Node* newFront = head->next->next;
            delete head->next;
            newFront->prev = head;
            head->next = newFront;
            listSize --;
        }
    }

    int front() { return head->next->data; }

    int back() { return tail->prev->data; }

    void clear() {
        while (listSize > 0) { pop_back(); }
    }

    int operator[] (int index) const {
        if (index < listSize && index >= 0) {
            Node* curr = head->next;
            for (int i = 0; i < index; i++) {
                curr = curr->next;
            }
            return curr->data;
        }
    }

    int& operator[] (int index) {
        if (index < listSize && index >= 0) {
            Node* curr = head->next;
            for (int i = 0; i < index; i++) {
                curr = curr->next;
            }
            return curr->data;
        }
    }

    Iterator begin() const {
        Iterator result = head->next;
        return result;
    }

    Iterator end() const {
        Iterator result = tail->prev;
        return result;
    }

    Iterator insert(const Iterator& iter, int data ) {
        Node* left = iter.nodePtr;
        Node* right = iter.nodePtr;
        right = right->next;

        Node* curr = new Node(data, left, right);
        left->next = curr;
        right->prev = curr;

        Iterator ans(curr);
        ++listSize;
        return ans;
    }

    Iterator erase(const Iterator& iter) {
        if (listSize > 0) {
            Node* left = iter.nodePtr;
            Node* curr = iter.nodePtr;
            Node* right = iter.nodePtr;
            left = left->prev;
            right = right->next;
            left->next = right;
            right->prev = left;
            delete curr;
            -- listSize;
            Iterator ans(right);
            return ans;
        }
    }

private:
    struct Node {
        Node(int newData, Node* prev, Node* next)
            : data(newData), prev(prev), next(next) {}
        int data;
        Node* next;
        Node* prev;
    };
    Node* head;
    Node* tail;
    int listSize;
};

void printListInfo(List& myList) {
    cout << "size: " << myList.size()
         << ", front: " << myList.front()
         << ", back(): " << myList.back()
         << ", list: " << myList << endl;
}

int main() {

    // Task 1
    cout << "\n------Task One------\n";
    List myList;
    myList.printInfo();
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i*i << ");\n";
        myList.push_back(i*i);
        // printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";

    // Task2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i*i << ");\n";
        myList.push_front(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    cout << "===================\n";

    // Task3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";

    // // Task4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;

    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    printListInfo(myList);
    cout << "Now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the iterator type directly:\n";
    for (List::Iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";


    // Task 6
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
         << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
    printListInfo(myList);
    // ***Need test for insert other than begin/end***
    cout << "===================\n";

    // Task 7
    cout << "\n------Task Seven------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    // myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    // cout << myList << '\n';
    myList.insert(myList.end(), 7);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    // ***Need test for erase other than begin/end***
    cout << "===================\n";

    // // Task 8
    // cout << "\n------Task Eight------\n";
    // cout << "Copy control\n";
    // cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    // myList.clear();
    // for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    // printListInfo(myList);
    // cout << "Calling doNothing(myList)\n";
    // doNothing(myList);
    // cout << "Back from doNothing(myList)\n";
    // printListInfo(myList);

    // cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
    // List listTwo;
    // for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
    // printListInfo(listTwo);
    // cout << "listTwo = myList\n";
    // listTwo = myList;
    // cout << "myList: ";
    // printListInfo(myList);
    // cout << "listTwo: ";
    // printListInfo(listTwo);
    // cout << "===================\n";
}
