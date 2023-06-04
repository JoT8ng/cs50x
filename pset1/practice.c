// Mario grid practice
#include <cs50.h>
#include <stdio.h>

int get_size(void);
void print_grid(int n);

// Main execution code
int main(void)
{
    int n = get_size();
    print_grid(n);
}

// Prompt user get size of grid
int get_size(void)
{
    int n;
    do
    {
        n = get_int("Size: ");
    }
    while (n < 1);
    return n;
}

// Print grid function
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