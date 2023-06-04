#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool character_quantity(string t);

int main(int argc, string argv[])
{
    // Prompt user for key
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (character_quantity(argv[1]) == false)
    {
        printf("Key must contain 26 characters\n");
        return 1;
    }

    // Prompt user for plaintext
    string plaintext = get_string("plaintext: ");

    // Substitute plaintext to ciphertext
    string key = argv[1];
    int index = 0;

    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (isupper(plaintext[i]))
        {
            index = plaintext[i] - 65;
            plaintext[i] = toupper(key[index]);
        }
        else if (islower(plaintext[i]))
        {
            index = plaintext[i] - 97;
            plaintext[i] = tolower(key[index]);
        }
        else
        {
            plaintext[i] = plaintext[i];
        }
    }

    // Print ciphertext
    printf("ciphertext: %s\n", plaintext);
}

// Check key
bool character_quantity(string t)
{
    // Check key count
    if (strlen(t) != 26)
    {
        return false;
    }
    for (int i = 0; i < strlen(t); i++)
    {
        // Check key if alphabet character
        if (!isalpha(t[i]))
        {
            return false;
        }
        // Check key if duplicates
        for (int j = i + 1; j < strlen(t); j++)
        {
            if (t[i] == t[j])
            {
                return false;
            }
        }
    }
    return true;
}