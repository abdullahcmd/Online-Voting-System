#ifndef CLASS_C_H
#define CLASS_C_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>

class VoterNode {
public:
    int cnic;
    VoterNode *left, *right;

    VoterNode(int cnic) {
        this->cnic = cnic;
        this->left = nullptr;
        this->right = nullptr;
    }
};

VoterNode* insertIntoBST(VoterNode* root, int cnic) {
    if (root == nullptr) {
        return new VoterNode(cnic);
    }

    if (cnic < root->cnic) {
        root->left = insertIntoBST(root->left, cnic);
    }
    else if (cnic > root->cnic) {
        root->right = insertIntoBST(root->right, cnic);
    }

    return root;
}


void saveToFileInorder(VoterNode* root, ofstream& outFile) {
    if (!root) {
        outFile << "00 ";
        return;
    }
    saveToFileInorder(root->left, outFile);
    outFile << root->cnic << " ";
    saveToFileInorder(root->right, outFile);
}

void saveBSTToFile(VoterNode* root, const string& filename) {
    try {
        ofstream outFile(filename);
        if (!outFile) {
            throw ios_base::failure("Error: Unable to open file for writing.");
        }
        saveToFileInorder(root, outFile);
        outFile.close();
    }
    catch (const exception& e) {
        cerr << "Error saving BST: " << e.what() << endl;
    }
}


VoterNode* loadBSTFromFile(const string& filename) {
    try {
        ifstream inFile(filename);
        if (!inFile) {
            throw std::ios_base::failure("Error: Unable to open file for reading.");
        }
        VoterNode* root = nullptr;
        vector<int> values;
        string value;
        while (inFile >> value) {
            if (value != "00") {
                values.push_back(stoi(value));
            }
        }

       
        for (int cnic : values) {
            root = insertIntoBST(root, cnic);
        }

        inFile.close();
        return root;

    }
    catch (const exception& e) {
        cerr << "Error loading BST: " << e.what() << endl;
        return nullptr;
    }
}

// Display functions
void displayBSTInOrder(VoterNode* root) {
    if (root == nullptr) {
        return;
    }
    displayBSTInOrder(root->left);
    cout << "CNIC: " << root->cnic <<endl;
    displayBSTInOrder(root->right);
}
bool searchInBST(VoterNode* root, int cnic) {
    if (root == nullptr) {
        return false;  // Base case: If tree is empty or node not found
    }

    if (root->cnic == cnic) {
        return true;  // CNIC found
    }

    if (cnic < root->cnic) {
        return searchInBST(root->left, cnic);  // Search in the left subtree
    }

    return searchInBST(root->right, cnic);  // Search in the right subtree
}

#endif