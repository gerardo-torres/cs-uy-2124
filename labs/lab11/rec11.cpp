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

#include <string>
#include <vector>
#include <iostream>

using namespace std;

// Node to be used a part of linked list
struct Node {
	Node(int data = 0, Node* next = nullptr) 
    : data(data), next(next) {}
	int data;
	Node* next;
};

// listInsertHead: adds a data item to the beginning of a [possibly empty] list
void listInsertHead(Node*& headPtr, int entry) {
	headPtr = new Node(entry, headPtr);
}

// listClear: frees up all the nodes in a list
void listClear(Node*& headPtr) {
    while (headPtr) {
        Node* next = headPtr->next;
        delete headPtr;
        headPtr = next;
    }
}

// listBuild: constructs a list from a vector of data items. Note that
// you can use a curly-braced sequence.
// This may be useful for setting up test cases. Feel free to use it
// or not as you like.
// Example of using would be:
//    Node* myList = listBuild({1, 4, 9, 16}); // builds a list of: 1 4 9 16
Node* listBuild(const vector<int>& vals) {
    Node* result = nullptr;
    for (size_t index = vals.size(); index > 0; --index) {
        listInsertHead(result, vals[index-1]);
    }
    return result;
}

// Task One
void splice(Node*& addedHead, Node*& splicedIntoHead) {
    Node* tempNext = splicedIntoHead->next;
    if (tempNext) {
        Node *curr = addedHead;
        splicedIntoHead->next = addedHead;
        while (curr->next) {
            curr = curr->next;
        }
        curr->next = tempNext;
    } else {
        splicedIntoHead->next = addedHead;
    }
}

Node* searchSubList(Node*&searchHead, Node*& sublistHead) {
    Node* left = sublistHead;
    Node* curr = searchHead;
    while (curr) {
        if (left->data != curr->data) {
            return nullptr;
        }
        left = left->next;
        curr = curr->next;
    }
    return sublistHead;
}

// Task Two
Node* isSublist(Node*& searchHead, Node*& subjectHead) {
    Node* curr = subjectHead;
    while (curr) {
        if (curr->data == searchHead->data) {
            Node* answer = searchSubList(searchHead, curr);
            if (answer != nullptr) { 
                return answer; 
            }
        }
        curr = curr->next;
    }
    cout << "fail to match\n";
    return nullptr;
}

void printList(Node*& head) {
    Node* curr = head;
    while (curr) {
        cout << curr->data;
        curr = curr->next;
        if (curr) {
            cout << " -> ";
        }
    }
    cout << '\n';
}

void printAddresses(Node*& head) {
    Node* curr = head;
    while (curr) {
        cout << curr->data << '\t' << &curr << '\n';
        curr = curr->next;
    }
}

void taskOne() {
    Node* head1 = listBuild({5, 7, 9, 1});
    Node* head2 = listBuild({6});
    cout << "lists before splicing: \n";
    printList(head1);
    printList(head2);
    Node* splicedIntoHead = head1->next;
    splice(head2, splicedIntoHead);
    cout << "lists after splicing: \n";
    printList(head1);
}

void taskTwo() {
    // Node* head1 = listBuild({5, 7, 6, 3, 2, 9, 1});
    // Node* head2 = listBuild({6, 3, 2, 9});
    Node *head1 = listBuild({5, 0, 2,0,2, 5, 3, 2});
    Node *head2 = listBuild({8, 8, 2});
    // cout << isSublist(head2, head1) << '\n';
    Node* output = isSublist(head2, head1);
    printList(output);
}

int main() {
    // taskOne();
    taskTwo();
}
