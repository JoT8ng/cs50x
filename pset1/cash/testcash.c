#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Ask how many cents the customer is owed
    int cents;
    do
    {
        cents = get_int("Change Owed: ");
    }
    while (cents < 1);

    // Loop to calculate number of quarters
    int quarters = 0;
    while (cents > 1)
    {
        cents = cents - 25;
        quarters++;
    }

    // Calculate the number of quarters to give the customer
    cents = cents - quarters * 25;

    // Loop to calculate number of dimes
    int dimes = 0;
    while (cents > 1)
    {
        cents = cents - 10;
        dimes++;
    }

    // Calculate the number of dimes to give the customer
    cents = cents - dimes * 10;

    // Sum coins
    int coins = quarters + dimes;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}