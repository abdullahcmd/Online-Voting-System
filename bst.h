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

    
    VoterNode(int cnic) {
        this->cnic = cnic;
        this->left = nullptr;
        this->right = nullptr;
    }

};


// Corrected insertIntoBST method
VoterNode* insertIntoBST(VoterNode* root, userInfo* temp) {
    // Base case: If the root is null, create a new node and return it
    if (root == nullptr) {
        return new VoterNode(temp->cnic);
    }

    // Recursive case: insert into left or right subtree based on comparison
    if (temp->cnic < root->cnic) {
        root->left = insertIntoBST(root->left, temp);  // Insert into left subtree
    } else if (temp->cnic > root->cnic) {
        root->right = insertIntoBST(root->right, temp);  // Insert into right subtree
    }

    // Return the root after insertion (unchanged for root node)
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
#endif;