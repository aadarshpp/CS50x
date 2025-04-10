#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool cycle(int, int);
bool check_cycle(int, int);
int pair_strength(pair);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
        for (int j = i + 1; j < candidate_count; j++)
            preferences[ranks[i]][ranks[j]]++;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;
    for (int i = 0; i < candidate_count; i++)
        for (int j = 0; j < candidate_count; j++)
            if (i != j && (preferences[i][j] - preferences[j][i]) > 0)
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int i, j;
    pair key;
    for (i = 1; i < pair_count; i++)
    {
        key = pairs[i];
        j = i - 1;

        while (j >= 0 && pair_strength(pairs[j]) < pair_strength(key))
        {
            pairs[j + 1] = pairs[j];
            j--;
        }
        pairs[j + 1] = key;
    }
}

// Return strength of a pair
int pair_strength(pair p)
{
    return preferences[p.winner][p.loser] - preferences[p.loser][p.winner];
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        pair p = pairs[i];
        if (!cycle(p.winner, p.loser))
            locked[p.winner][p.loser] = true;
    }
}

// Checks if adding an edge (i, j) forms a cycle
bool cycle(int i, int j)
{
    locked[i][j] = true;

    // Check if the newly added edge caused a cycle formation
    bool has_cycle = check_cycle(j, i);

    locked[i][j] = false;

    return has_cycle;
}

// Check if there is a cycle involving start
bool check_cycle(int curr, int start)
{
    if (curr == start)
        return true;

    for (int j = 0; j < candidate_count; j++)
        if (locked[curr][j])
            if (check_cycle(j, start))
                return true;

    return false;
}

// Print the winner of the election
void print_winner(void)
{
    bool undominated[candidate_count];
    for (int i = 0; i < candidate_count; i++)
        undominated[i] = true;

    for (int j = 0; j < candidate_count; j++)
        for (int i = 0; i < candidate_count; i++)
            if (locked[i][j])
            {
                undominated[j] = false;
                break;
            }

    for (int i = 0; i < candidate_count; i++)
        if (undominated[i])
        {
            printf("%s\n", candidates[i]);
            break;
        }
}
