// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <cs50.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Choose number of buckets in hash table
const unsigned int N = 5000;

// Variable for size of dictionary
int word_count = 0;

// Hash index
int hash_code = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Access linked list at index in the hash table
    hash_code = hash(word);

    // Initiate cursor
    node *cursor = table[hash_code];

    // Traverse linked list looking for the word strcasecmp
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Hash word according to sum of ASCII values
    unsigned int hash = 0;

    for (int i = 0; word[i] != '\0'; i++)
    {
        hash += toupper(word[i]);
    }

    // If function ends up with value greater than N (buckets)
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Load dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Initiate word variable
    char word[LENGTH + 1];

    // Read strings from file one at a time
    while (fscanf(file, "%s", word) != EOF)
    {
        // Create a new node for each word
        node *n = malloc(sizeof(node));

        // Copy word into node
        strcpy(n->word, word);

        // Check if return value is null
        if (n == NULL)
        {
            return false;
        }

        // Hash word to obtain a hash value
        hash_code = hash(word);

        // Insert node into hash table at that location
        n->next = NULL;

        // Add node to linked list
        n->next = table[hash_code];

        // Prepend node in linked list
        table[hash_code] = n;

        word_count++;
    }

    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (word_count > 0)
    {
        return word_count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Traverse through hash table buckets
    for (int i = 0; i < N; i++)
    {
        // Initiate cursor
        node *cursor = table[i];

        // Traverse through linked list freeing nodes
        while (cursor != NULL)
        {
            // Initiate temp pointer
            node *temp = cursor;

            cursor = cursor->next;
            free(temp);
        }

        // When cursor reaches last bucket and end of the linked list
        if (i == N - 1 && cursor == NULL)
        {
            return true;
        }
    }
    return false;
}
