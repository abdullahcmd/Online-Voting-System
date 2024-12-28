#include <iostream>
using namespace std;
#include <fstream>
#ifndef CLASS_A_H
#define CLASS_A_H
#include <sstream>
class userInfo
{

public:
    int cnic;
    string name;
    string address;
    userInfo *left;
    int age;
    userInfo *right;
    userInfo(){}

    userInfo(int cnic, string name, int age, string address)
    {

        this->age = age;
        this->cnic = cnic;
        this->name = name;
        this->address = address;
        this->left = nullptr;
        this->right = nullptr;
    }
};
userInfo *insertNode(userInfo *&head, userInfo *&tail, int cnic, string name, int age, string address)
{
    userInfo *newNode = new userInfo(cnic, name, age, address);
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

userInfo *displayList(userInfo *head)
{
    userInfo *current = head;
    while (current != nullptr)
    {
        cout << "CNIC: " << current->cnic
             << ", Name: " << current->name
             << ", Age: " << current->age
             << ", Address: " << current->address << endl;
        current = current->right;
    }
    return head;
}

userInfo *readDataFromCSV(const string &filename, userInfo *&head, userInfo *&tail)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Failed to open file: " << filename << endl;
        return nullptr;
    }

    string line;

    getline(file, line);

    while (getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        stringstream ss(line);
        string cnicStr, name, ageStr, address;

        getline(ss, cnicStr, ',');
        getline(ss, name, ',');
        getline(ss, ageStr, ',');
        getline(ss, address);

        if (cnicStr.empty() || name.empty() || ageStr.empty() || address.empty())
        {
            cerr << "Skipping malformed line: " << line << endl;
            continue;
        }

        int cnic = stoi(cnicStr);
        int age = stoi(ageStr);

        insertNode(head, tail, cnic, name, age, address);
    }

    file.close();
    return head;
}
userInfo *authentication(int cnic, userInfo *&head)
{

    userInfo *temp = head;
    while (temp != NULL)
    {
        if (temp->cnic == cnic)
        {
            cout << "User is registered" << endl;
            cout<<endl;
            return temp;
            break;
        }
        else
        {
            temp = temp->right;
            if (temp->right == NULL && temp->cnic != cnic)
            {
                cout << "Voter ID is not registered" << endl;
                cout<<endl;
                return nullptr;
            }
        }
    }
}
#endif