#include <iostream>
using namespace std;
#include "LinkedList.h"

#ifndef CLASS_A_H
#define CLASS_A_H


class VoterNode {
public:
    int cnic;
    string name;
    int age;
    string address;
    VoterNode *left, *right;

    
    VoterNode(int cnic, string name, int age, string address) {
        this->cnic = cnic;
        this->name = name;
        this->age = age;
        this->address = address;
        this->left = nullptr;
        this->right = nullptr;
    }
};


VoterNode* insertIntoBST(VoterNode* root, int cnic, string name, int age, string address) {
    if (root == nullptr) {
        return new VoterNode(cnic, name, age, address);
    }
    if (cnic < root->cnic) {
        root->left = insertIntoBST(root->left, cnic, name, age, address);
    } else if (cnic > root->cnic) {
        root->right = insertIntoBST(root->right, cnic, name, age, address);
    }
    return root;
}


void displayBSTInOrder(VoterNode* root) {
    if (root == nullptr) {
        return;
    }
    displayBSTInOrder(root->left);
    cout << "CNIC: " << root->cnic
         << ", Name: " << root->name
         << ", Age: " << root->age
         << ", Address: " << root->address << endl;
    displayBSTInOrder(root->right);
}


VoterNode* addVotedUsersToBST(userInfo* head) {
    VoterNode* root = nullptr;
    userInfo* current = head;

    while (current != nullptr) {
        char hasVoted;
        cout << "Has user with CNIC " << current->cnic << " voted? (y/n): ";
        cin >> hasVoted;

        if (tolower(hasVoted) == 'y') {
            root = insertIntoBST(root, current->cnic, current->name, current->age, current->address);
        }

        current = current->right; 
    }
    return root;
}