#include <iostream>
using namespace std;
#include <fstream>
#include <sstream>
#ifndef CLASS_B_H
#define CLASS_B_H
class candidate
{

public:
    int cnic;
    string name;
    string address;
    candidate *left;
    int age;
    int votes;
    string symbol;
    candidate *right;

    candidate(int cnic, string name, int age, string address,string symbol,int votee)
    {
        votes=votee;
        this->age = age;
        this->cnic = cnic;
        this->name = name;
        this->address = address;
        this->left= nullptr;
        this->right= nullptr;
        this->symbol=symbol;
    }
};
    candidate* insertNode(candidate *&head,  candidate*&tail, int cnic, string name, int age, string address,string symbol,int votes)
    {
        candidate *newNode = new candidate(cnic, name, age, address,symbol,votes);
        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->right = newNode;
            newNode->left = tail;
            tail = newNode;
        }
    }


   candidate* displayList(candidate* head) {
    candidate* current = head;
    while (current != nullptr) {
        cout << "CNIC: " << current->cnic
             << ", Name: " << current->name
             << ", Age: " << current->age
             << ", Symbol: " << current->symbol
             << ", Address: " << current->address << endl;
        current = current->right;
    }
    return head ;
}

candidate* readCadDataFromCSV(const string& filename, candidate*& head, candidate*& tail) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return nullptr; 
    }

    string line;

   
    getline(file, line);

 
    while (getline(file, line)) {
        if (line.empty()) {
            continue; 
        }

        stringstream ss(line);
        string cnicStr, name, ageStr, address, symbol,votesStr;

        
        getline(ss, cnicStr, ',');
        getline(ss, name, ',');
        getline(ss, ageStr, ',');
        getline(ss, address,',');
        getline(ss, symbol,',');
        getline(ss, votesStr);
      

       
        if (cnicStr.empty() || name.empty() ||symbol.empty() || ageStr.empty() || address.empty()) {
            cerr << "Skipping malformed line: " << line << endl;
            continue;
        }

       
        int cnic = stoi(cnicStr);
        int age = stoi(ageStr);
        int votes = stoi(votesStr);

       
        insertNode(head, tail, cnic, name, age, address, symbol,votes);
    }

    file.close();
    return head; 
}
#endif