#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Nested loop to loop through height and width of 2D pixel image matrix
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];

            // Change all black pixels to a color of your choosing
            if (pixel.rgbtBlue == 0x00 && pixel.rgbtGreen == 0x00 && pixel.rgbtRed == 0x00)
            {
                pixel.rgbtBlue = 0xd8;
                pixel.rgbtGreen = 0x72;
                pixel.rgbtRed = 0xB1;
            }
            image[i][j] = pixel;
        }
    }
}
