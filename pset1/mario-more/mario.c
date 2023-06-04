#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt for height
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Build pyramid
    for (int i = 0; i < height; i++)
    {
        // Loop for left aligned space
        for (int k = height; k > i + 1; k--)
        {
            printf(" ");
        }
        // Loop for right aligned pyramid
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        // Loop for spaces separating pyramids
        for (int m = 0; m < 1; m++)
        {
            printf("  ");
        }
        // Loop for second left aligned pyramid
        for (int l = 0; l <= i; l++)
        {
            printf("#");
        }
        printf("\n");
    }
}