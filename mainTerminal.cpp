#include <iostream>
#include "LinkedList.h"
#include "candidate.h"
#include "BST.h"
#include "priorityQueue.h"
#include <cctype>
using namespace std;

void castVote(int voterID, userInfo *tempVoter, candidate *tempcad, userInfo *head, candidate *cad_head, VoterNode *&root)
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
        if (tempcad == NULL)
        {
            tempcad = cad_head;
        }
        cout << "Enter the candidate symbol: " << endl;
        string symbol;
        cin >> symbol;
        // uppercasing the users input symbol
        for (char &c : symbol)
        {
            c = toupper(c);
        }
        bool candidateFound = false;
        while (tempcad != nullptr)
        {
            if (symbol == tempcad->symbol)
            {
                cout << " The candidate has been found.";
                tempcad->votes++;
                cout << tempcad->votes;
                candidateFound = true;
                break;
            }
            else
            {
                tempcad = tempcad->right;
            }
        }

        if (!candidateFound)
        {
            cout << "The candidate was not found.";
        }

        insertIntoBST(root, tempVoter->cnic);
        saveBSTToFile(root, "BST.txt");
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
    VoterNode *root = new VoterNode(0);
    // BST FILE ADDED
    string bstfilename = "BST.txt";
    VoterNode *loadedRoot = loadBSTFromFile(bstfilename);
    cout << "BST loaded from file:" << endl;
    // PRIORITY QUEUE
    priority_queue<CandidatePriority> pq;
    priority_queue<CandidatePriority> loadedPQ;

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
            castVote(voterID, tempVoter, tempcad, head, cad_head, loadedRoot);
            break;
        case 2:
            pq = createPriorityQueue(cad_head);
            displayPriorityQueue(pq);
            savePriorityQueueToFile(pq, "votes.txt");

            loadedPQ = loadPriorityQueueFromFile("votes.txt");

            displayPriorityQueue(loadedPQ);
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