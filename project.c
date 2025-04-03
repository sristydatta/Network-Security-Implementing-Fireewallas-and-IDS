#include <stdio.h>
#include <string.h>

// Define maximum sizes
#define MAX_VOTERS 100
#define MAX_CANDIDATES 5
#define NAME_LENGTH 50

// Define a structure for a voter
typedef struct {
    int voterID;
    char name[NAME_LENGTH];
    int hasVoted;  // 0 = Not voted, 1 = Voted
} Voter;

// Define a structure for a candidate
typedef struct {
    int candidateID;
    char name[NAME_LENGTH];
    int voteCount;
} Candidate;

// Global arrays
Voter voters[MAX_VOTERS];
Candidate candidates[MAX_CANDIDATES];
int voterCount = 0;
int candidateCount = 0;

// Function to register a voter
void registerVoter(int voterID, char name[]) {
    if (voterCount < MAX_VOTERS) {
        voters[voterCount].voterID = voterID;
        strcpy(voters[voterCount].name, name);
        voters[voterCount].hasVoted = 0;  // Initially, the voter has not voted
        voterCount++;
        printf("Voter registered successfully: ID=%d, Name=%s\n", voterID, name);
    } else {
        printf("Cannot register more voters. Limit reached.\n");
    }
}

// Function to display candidates
void displayCandidates() {
    printf("\nList of Candidates:\n");
    for (int i = 0; i < candidateCount; i++) {
        printf("Candidate ID: %d, Name: %s\n", candidates[i].candidateID, candidates[i].name);
    }
}

// Function to check if a voter is eligible to vote
int checkVoterEligibility(int voterID) {
    for (int i = 0; i < voterCount; i++) {
        if (voters[i].voterID == voterID) {
            if (voters[i].hasVoted == 0) {
                return 1;  // Eligible to vote
            } else {
                return 0;  // Already voted
            }
        }
    }
    return -1;  // Voter not found
}

// Function to cast a vote
void vote(int voterID, int candidateID) {
    int voterIndex = -1;
    int candidateIndex = -1;

    // Find the voter
    for (int i = 0; i < voterCount; i++) {
        if (voters[i].voterID == voterID) {
            voterIndex = i;
            break;
        }
    }

    // Find the candidate
    for (int i = 0; i < candidateCount; i++) {
        if (candidates[i].candidateID == candidateID) {
            candidateIndex = i;
            break;
        }
    }

    if (voterIndex == -1) {
        printf("Voter not found.\n");
    } else if (candidateIndex == -1) {
        printf("Candidate not found.\n");
    } else if (voters[voterIndex].hasVoted == 1) {
        printf("Voter has already voted.\n");
    } else {
        candidates[candidateIndex].voteCount++;
        voters[voterIndex].hasVoted = 1;
        printf("Vote cast successfully: Voter ID=%d, Candidate ID=%d\n", voterID, candidateID);
    }
}

// Function to display election results
void displayResults() {
    printf("\nElection Results:\n");
    for (int i = 0; i < candidateCount; i++) {
        printf("Candidate ID: %d, Name: %s, Votes: %d\n",
               candidates[i].candidateID, candidates[i].name, candidates[i].voteCount);
    }
}

// Main program
int main() {
    // Register some candidates
    candidates[0] = (Candidate){1, "Alice", 0};
    candidates[1] = (Candidate){2, "Bob", 0};
    candidates[2] = (Candidate){3, "Charlie", 0};
    candidateCount = 3;

    // Register some voters
    registerVoter(101, "John Doe");
    registerVoter(102, "Jane Smith");
    registerVoter(103, "Mike Johnson");

    // Display candidates
    displayCandidates();

    // Simulate voting
    vote(101, 1);  // John votes for Alice
    vote(102, 2);  // Jane votes for Bob
    vote(103, 1);  // Mike votes for Alice
    vote(101, 2);  // John tries to vote again (should fail)

    // Display results
    displayResults();

    return 0;
}
