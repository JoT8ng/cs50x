// Make mario grid practice 1
#include <cs50.h>
#include <stdio.h>

int get_size(void);
void print_grid(int n);

// Main code execution
int main(void)
{
    int n = get_size();
    print_grid(n);
}

// Prompt grid size
int get_size(void)
{
    int n;
    do
    {
        get_int("Size: ");
    }
    while (n < 1);
    return n;
}

// Print grid
void print_grid(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}