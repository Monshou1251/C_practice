#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // Iterate through the candidates to find a match for the given name
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if the name matches the candidate's name
        if (strcmp(candidates[i].name, name) == 0)
        {
            // Update preferences array with the candidate index as the rank preference
            preferences[voter][rank] = i;
            return true; // Successfully recorded the preference
        }
    }

    // If no match found, return false
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // Iterate through each voter
    for (int i = 0; i < voter_count; i++)
    {
        // Iterate through the voter's preferences
        for (int j = 0; j < candidate_count; j++)
        {
            // Get the candidate index based on the current preference
            int candidate_index = preferences[i][j];

            // Check if the candidate is not eliminated
            if (!candidates[candidate_index].eliminated)
            {
                // Update the candidate's votes and break out of the loop
                candidates[candidate_index].votes++;
                break;
            }
        }
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // Calculate the number of votes needed to win the election
    int votes_needed = voter_count / 2 + 1;

    // Iterate through the candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if the candidate has more than half of the votes
        if (candidates[i].votes >= votes_needed)
        {
            // Print the winner's name
            printf("%s\n", candidates[i].name);

            // Return true indicating a winner
            return true;
        }
    }

    // No winner found
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // Initialize the minimum votes with the maximum possible value
    int min_votes = MAX_VOTERS + 1;

    // Iterate through the candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if the candidate is still in the election
        if (!candidates[i].eliminated)
        {
            // Update the minimum votes if the candidate has fewer votes
            if (candidates[i].votes < min_votes)
            {
                min_votes = candidates[i].votes;
            }
        }
    }

    // Return the minimum votes
    return min_votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // Iterate through the candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if the candidate is still in the election and has a different number of votes than the minimum
        if (!candidates[i].eliminated && candidates[i].votes != min)
        {
            // If any candidate has a different number of votes, it's not a tie
            return false;
        }
    }

    // If all remaining candidates have the same number of votes (equal to the minimum), it's a tie
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // Iterate through the candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if the candidate is still in the election and has the minimum number of votes
        if (!candidates[i].eliminated && candidates[i].votes == min)
        {
            // Eliminate the candidate
            candidates[i].eliminated = true;
        }
    }
}
