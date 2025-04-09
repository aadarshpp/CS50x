#include <cs50.h>

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define LIMIT 9

// Candidates have name and vote count
typedef struct
{
    char *name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[LIMIT];

// Number of candidates
int candidate_count;

// Function prototypes
int max(int, int);
void print_winner(void);
bool vote(char *name);

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: ./plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > LIMIT)
    {
        printf("Maximum number of candidates is %i\n", LIMIT);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count;
    printf("Number of voters: ");
    scanf("%d", &voter_count);
    getchar();

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        char name[20];
        printf("Vote: ");
        scanf("%s", name);

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
bool vote(char *name)
{
    for (int i = 0; i < candidate_count; i++)
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes += 1;
            return true;
        }
    return false;
}

// Retuns maximum of two integers
int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int max_votes = 0;
    for (int i = 0; i < candidate_count; i++)
        max_votes = max(max_votes, candidates[i].votes);

    for (int i = 0; i < candidate_count; i++)
        if (candidates[i].votes == max_votes)
            printf("%s\n", candidates[i].name);
}
