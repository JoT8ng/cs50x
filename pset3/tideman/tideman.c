#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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
}
pair;

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
bool cycles(int winner, int loser);

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
    // Loop through candidates and compare strings
    for (int j = 0; j < candidate_count; j++)
    {
        if (strcmp(candidates[j], name) == 0)
        {
            ranks[rank] = j;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Nested loop of candidates to fill in preferences matrix
    for (int j = 0; j < candidate_count; j++)
    {
        for (int k = j + 1; k < candidate_count; k++)
        {
            preferences[ranks[j]][ranks[k]] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Nested loop to run through matrix of preferences and compare them
    pair_count = 0;

    for (int j = 0; j < candidate_count; j++)
    {
        for (int k = j + 1; k < candidate_count; k++)
        {
            if (preferences[j][k] > preferences[k][j])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = k;
                pair_count++;
            }
            if (preferences[k][j] > preferences[j][k])
            {
                pairs[pair_count].winner = k;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Create strength variable and temporary array
    int max_strength;
    int temp_winner[pair_count];
    int temp_loser[pair_count];
    int strength;

    // Sort pairs algorithm
    for (int i = 0; i < pair_count; i++)
    {
        // Have to apply strength of victory to each pair
        max_strength = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
        for (int j = i + 1; j < pair_count; j++)
        {
            strength = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
            if(max_strength < strength)
            {
                max_strength = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];

                // Sort re-shuffle pairs array
                temp_winner[i] = pairs[j].winner;
                temp_loser[i] = pairs[j].loser;

                pairs[j].winner = pairs[i].winner;
                pairs[j].loser = pairs[i].loser;

                pairs[i].winner = temp_winner[i];
                pairs[i].loser = temp_loser[i];
            }
        }
    }
    return;
}

// New boolean function to check for cycles
bool cycles(int winner, int loser)
{
    // State that if there is an edge between loser and winner that cycle is true
    if (locked[loser][winner] == true)
    {
        return true;
    }

    // Check for edges between all losers and winners using recursion
    for (int i = 0; i < pair_count; i++)
    {
        if (locked[loser][i] && cycles(winner, i))
        {
            return true;
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Loop through pair array and if statement taking boolean results from cycles function
    for (int i = 0; i < pair_count; i++)
    {
        if (!cycles(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // Loop through candidates and determine the candidate that is the source
    int i;

    for (i = 0; i < candidate_count; i++)
    {
        int x = 1;

        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                x = 0;
            }
        }

        if (x == 1)
        {
            break;
        }
    }
    printf("%s\n", candidates[i]);
    return;
}