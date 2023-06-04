#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Prompt for name
    string name = get_string("What is your name? ");

    // Print response and name
    printf("hello, %s\n", name);
}