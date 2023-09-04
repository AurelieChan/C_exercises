#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{

    // TODO
    //Look for candidates in the given list
    for (int i = 0; i < candidate_count; i++)
    {

        if (strcmp(name, candidates[i].name) == 0)
        {

            //If candidate found, update their vote total
            candidates[i].votes++;

            return true;

        }

    }

    //If no candidate found, do not update ant vote totals and return false.
    return false;

}

// Sort candidates and print winner(s)
void print_winner()
{

    string temp1;
    int temp2;
    int k = 0;

    //Sort candidats from the highest votes to smallest
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {

            if (candidates[i].votes < candidates[j].votes)
            {

                temp2 = candidates[i].votes;
                temp1 = candidates[i].name;
                candidates[i].votes = candidates[j].votes;
                candidates[i].name = candidates[j].name;
                candidates[j].votes = temp2;
                candidates[j].name = temp1;

            }

        }

    }

    do
    {

        //print winner(s)
        printf("%s\n", candidates[k].name);

        k++;

    }
    while (candidates[k].votes == candidates[0].votes);

}