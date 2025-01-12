#include <iostream>
#include <queue>
#include <string>
#include "Candidate.h"
using namespace std;

struct CandidatePriority
{
    string name;
    int votes;

    CandidatePriority(string n, int v)
    {

        name = n;
        votes = v;
    }
    bool operator<(const CandidatePriority& other) const
    {
        return votes < other.votes;  // Comparing votes for priority
    }
};

priority_queue<CandidatePriority> createPriorityQueue(candidate *head)
{
    priority_queue<CandidatePriority> pq;

    candidate *current = head;
    while (current != nullptr)
    {
        pq.push(CandidatePriority(current->name, current->votes));
        current = current->right;
    }

    return pq;
}

void displayPriorityQueue(priority_queue<CandidatePriority> pq)
{
    cout << "\nCandidates ordered by vote count (highest to lowest):\n";
    while (!pq.empty())
    {
        CandidatePriority cp = pq.top();
        cout << "Name: " << cp.name << ", Votes: " << cp.votes << endl;
        pq.pop();
    }
}
void savePriorityQueueToFile(priority_queue<CandidatePriority> pq, const string& filename)
{
    ofstream outFile(filename);  // Open the file for writing

    if (outFile.is_open())  // Check if the file opened successfully
    {
        while (!pq.empty())
        {
            CandidatePriority cp = pq.top();
            outFile << cp.name << "," << cp.votes << endl;  // Save name and votes to file
            pq.pop();
        }
        outFile.close();  // Close the file after writing
        cout << "Data successfully saved to " << filename << endl;
    }
    else
    {
        cout << "Unable to open file for writing!" << endl;
    }
}

priority_queue<CandidatePriority> loadPriorityQueueFromFile(const string& filename)
{
    ifstream inFile(filename);  // Open the file for reading
    priority_queue<CandidatePriority> pq;

    if (inFile.is_open())  // Check if the file opened successfully
    {
        string line;
        while (getline(inFile, line))  // Read each line from the file
        {
            stringstream ss(line);
            string name;
            int votes;
            getline(ss, name, ',');  // Extract name (separated by comma)
            ss >> votes;  // Extract votes
            pq.push(CandidatePriority(name, votes));  // Push the candidate to the priority queue
        }
        inFile.close();  // Close the file after reading
        cout << "Data successfully loaded from " << filename << endl;
    }
    else
    {
        cout << "Unable to open file for reading!" << endl;
    }

    return pq;
}