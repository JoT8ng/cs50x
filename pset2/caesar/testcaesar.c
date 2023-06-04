#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

bool only_digits(string s);

int main(int argc, string argv[])
{
    // Prompt user for key and check if digits
    if (argc == 2 || only_digits(argv[1]) == true)
    {
        return 0;
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Convert input string to int

    // Implement caesar cipher formula

    // Print encrypted text
}

bool only_digits(string s)
{
    for (int i = 0; i < strlen(s); i++)
    {
        if (isdigit(s[1]))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}



// working version
for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }