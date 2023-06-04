#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt user input for a card number
    long number;
    do
    {
        number = get_long("Number: ");
    }
    while (number < 0);

    // Check if input card number is a card number
    long card = number;
    long digits = 0;
    while (card != 0)
    {
        card = card / 10;
        digits++;
    }
    if (digits < 13 || digits > 16 || digits == 14)
    {
        printf("INVALID\n");
    }

    // Get sum of every other digit multiplied by 2
    long i = number;
    long firstsum = 0;
    long modulo = 0;
    long timestwo = 0;
    while (i > 0)
    {
        modulo = i % 100 / 10;
        timestwo = modulo * 2;
        if (timestwo >= 10)
        {
            firstsum = firstsum + (timestwo % 10) + (timestwo / 10);
        }
        else if (timestwo < 10)
        {
            firstsum = firstsum + timestwo;
        }
        i = i / 100;
    }

    // Get sum of digits not multiplied by 2
    long j = number;
    long secondsum = 0;
    long twomodulo = 0;
    while (j > 0)
    {
        twomodulo = j % 100;
        twomodulo = twomodulo % 10;
        secondsum = secondsum + twomodulo;
        j = j / 100;
    }

    // Add sum to sum of digits not multiplied by 2
    long checksum = firstsum + secondsum;

    // Check if total modulo 10 is congruent to 0 and card type
    long k = 0;
    long decimals = 10;
    for (k = 0; k < digits - 2; k++)
    {
        decimals = decimals * 10;
    }
    long firstdigit = number / decimals;
    long seconddigit = number / (decimals / 10);

    printf("First Digit: %li\n", firstdigit);
    printf("Second Digit: %li\n", seconddigit);
}