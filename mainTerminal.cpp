#include <iostream>
#include "LinkedList.h"
#include "candidate.h"
#include <cctype>
using namespace std;
void castVote(int voterID, userInfo *tempVoter, candidate *tempcad, userInfo *head, candidate *cad_head)
{
    cout << "Enter your Voter ID: " << endl;
    cin >> voterID;
    cout << endl;
    tempVoter = authentication(voterID, head);

    if (tempVoter != nullptr)
    {
        cout << "The candidate list is given below :" << endl;
        cout << endl;
    
    // Displayin the candidate linked list
    while (tempcad != NULL)
    {
        cout << "--" << tempcad->name << "---Voting Symbol: " << tempcad->symbol << endl;
        tempcad = tempcad->right;
      
    }
    // To point the candidate linked list again towards head. 
      if (tempcad==NULL)
        {
            tempcad = cad_head;
            
        }
    cout << "Enter the candidate symbol: " << endl;
    string symbol;
    cin >> symbol;
//uppercasing the users input symbol
    for (char &c : symbol)
    {
        c = toupper(c);
    }
//Matching the users symbol to the candidate symbol and if matched then incrementing the vote of that candidate.
    while (tempcad != nullptr)
    {
        if (symbol == tempcad->symbol)
        {
            cout << " The candidate has been found.";
            tempcad->votes++;
            cout<<tempcad->votes;
            break;
        }
        else
        {
            tempcad = tempcad->right;
        }
    }

    }
}

int main()
{
    // Voter Info
    userInfo *head = nullptr;
    userInfo *tail = nullptr;
    string filename = "user_data.csv";
    readDataFromCSV(filename, head, tail);
    userInfo *tempVoter = head;
    // Candidate Info
    candidate *cad_head = nullptr;
    candidate *cad_tail = nullptr;
    string cadfilename = "cad_data.csv";
    readCadDataFromCSV(cadfilename, cad_head, cad_tail);
    candidate *tempcad = cad_head;

    int choice;
    int voterID;

    while (true)
    {
        cout << "\n=== Online Voting System ===\n";
        cout << "1. Cast Vote\n";
        cout << "2. View Results (Admin Only)\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: " << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
            castVote(voterID, tempVoter, tempcad, head,cad_head);
            break;
        case 3:
            cout << "Thank you for using the Online Voting System!\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}