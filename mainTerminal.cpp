#include <iostream>
#include "LinkedList.h"
#include "candidate.h"
#include <cctype>
using namespace std;

void castVote (int voterID, userInfo *tempVoter,candidate* tempcad,userInfo* head)
{
        cout << "Enter your Voter ID: "<<endl;
            cin >> voterID;
            cout<<endl;
            tempVoter = authentication(voterID,head);
            if (tempVoter!=NULL)
            {
                cout << "The candidate list is given below :"<<endl;
                cout<<endl;
            }
            while (tempcad!=NULL&& tempVoter!=NULL)
           {
            cout<<"--"<<tempcad->name<<"---Voting Symbol: "<<tempcad->symbol<<endl;
            tempcad=tempcad->right;
            if (tempVoter->right==nullptr)
            {
                tempVoter=head;
                break;
            }
           }
           cout<<"Enter your choice: "<<endl;
            string symbol;
            cin>>symbol;

            for (char& c : symbol) {
            c = toupper(c);

            }

           cout << "Your choice in uppercase: " << symbol << endl;


}

int main()
{
    //Voter Info
    userInfo *head = nullptr;
    userInfo *tail = nullptr;
    string filename = "user_data.csv";
    readDataFromCSV(filename, head, tail);
    userInfo* tempVoter= head;
    //Candidate Info
    candidate*cad_head = nullptr;
    candidate *cad_tail = nullptr;
    string cadfilename = "cad_data.csv";
    readCadDataFromCSV(cadfilename, cad_head,cad_tail);
    candidate* tempcad = cad_head;

    int choice;
    int voterID;

    while (true)
    {
        cout << "\n=== Online Voting System ===\n";
        cout << "1. Cast Vote\n";
        cout << "2. View Results (Admin Only)\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: "<<endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
            castVote(voterID,tempVoter,tempcad,head);
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