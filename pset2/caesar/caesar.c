#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool only_digits(string s);
char rotate(char c, int n);

int main(int argc, string argv[])
{
    // Prompt user for key and check if digits
    if (argc != 2 || only_digits(argv[1]) == false)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Convert input string to int
    int key = atoi(argv[1]);

    // Implement caesar cipher formula or encipher
    string plaintext = get_string("Plaintext: ");

    for (int i = 0; i < strlen(plaintext); i++)
    {
        plaintext[i] = rotate(plaintext[i], key);
    }

    // Print encrypted text
    printf("Ciphertext: %s\n", plaintext);
}

bool only_digits(string s)
{
    for (int i = 0; i < strlen(s); i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}

char rotate(char c, int n)
{
    // Shift alphabetical index using forumla and convert ASCII to alphabetical index
    if (isupper(c))
    {
        c = (c - 65 + n) % 26 + 65;
    }
    else if (islower(c))
    {
        c = (c - 97 + n) % 26 + 97;
    }
    else
    {
        return c;
    }
    return c;
}