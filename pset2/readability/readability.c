#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Getting user input
    string t = get_string("Text: ");

    // Count letters
    int letters = count_letters(t);

    // Count words
    int words = count_words(t) + 1;

    // Count sentences
    int sentences = count_sentences(t);

    // Implement Coleman-Liau Index
    float L = ((float) letters / (float) words) * 100;
    float S = ((float) sentences / (float) words) * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    // Print Grade
    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int count_letters(string text)
{
    int nletters = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            nletters++;
        }
        else
        {
            nletters += 0;
        }
    }
    return nletters;
}

int count_words(string text)
{
    int nwords = 0;
    for (int j = 0, n = strlen(text); j < n; j++)
    {
        if (isspace(text[j]))
        {
            nwords++;
        }
        else
        {
            nwords += 0;
        }
    }
    return nwords;
}

int count_sentences(string text)
{
    int nsentences = 0;
    for (int k = 0, n = strlen(text); k < n; k++)
    {
        if (text[k] == '.' || text[k] == '!' || text[k] == '?')
        {
            nsentences++;
        }
        else
        {
            nsentences += 0;
        }
    }
    return nsentences;
}