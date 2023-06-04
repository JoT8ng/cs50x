#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Change all pixels from hexademical to float
            float b = image[i][j].rgbtBlue;
            float g = image[i][j].rgbtGreen;
            float r = image[i][j].rgbtRed;

            // Calculate the average
            int average = round((b + g + r) / 3.0);

            // Set pixels to average
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Change all pixels from hexademical to float
            float original_b = image[i][j].rgbtBlue;
            float original_g = image[i][j].rgbtGreen;
            float original_r = image[i][j].rgbtRed;

            // Sepia algorithm
            int sepiaRed = round(0.393 * original_r + 0.769 * original_g + 0.189 * original_b);
            int sepiaGreen = round(0.349 * original_r + 0.686 * original_g + 0.168 * original_b);
            int sepiaBlue = round(0.272 * original_r + 0.534 * original_g + 0.131 * original_b);

            // Check that no pixel is beyond 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // Set pixels to Sepia
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {

            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            temp[i][j] = image[i][j];

        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int counter = 0;
            float r = 0;
            float g = 0;
            float b = 0;

            // Center pixel
            if (i >= 0 && j >= 0)
            {
                r += temp[i][j].rgbtRed;
                g += temp[i][j].rgbtGreen;
                b += temp[i][j].rgbtBlue;
                counter++;
            }
            // Above pixel
            if (i - 1 >= 0)
            {
                r += temp[i - 1][j].rgbtRed;
                g += temp[i - 1][j].rgbtGreen;
                b += temp[i - 1][j].rgbtBlue;
                counter++;
            }
            // Bottom pixel
            if (i + 1 <= height - 1)
            {
                r += temp[i + 1][j].rgbtRed;
                g += temp[i + 1][j].rgbtGreen;
                b += temp[i + 1][j].rgbtBlue;
                counter++;
            }
            // Above left
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                r += temp[i - 1][j - 1].rgbtRed;
                g += temp[i - 1][j - 1].rgbtGreen;
                b += temp[i - 1][j - 1].rgbtBlue;
                counter++;
            }
            // Above right
            if (i - 1 >= 0 && j + 1 <= width - 1)
            {
                r += temp[i - 1][j + 1].rgbtRed;
                g += temp[i - 1][j + 1].rgbtGreen;
                b += temp[i - 1][j + 1].rgbtBlue;
                counter++;
            }
            // Bottom left
            if (i + 1 <= height - 1 && j - 1 >= 0)
            {
                r += temp[i + 1][j - 1].rgbtRed;
                g += temp[i + 1][j - 1].rgbtGreen;
                b += temp[i + 1][j - 1].rgbtBlue;
                counter++;
            }
            // Bottom right
            if (i + 1 <= height - 1 && j + 1 <= width - 1)
            {
                r += temp[i + 1][j + 1].rgbtRed;
                g += temp[i + 1][j + 1].rgbtGreen;
                b += temp[i + 1][j + 1].rgbtBlue;
                counter++;
            }
            // Left pixel
            if (j - 1 >= 0)
            {
                r += temp[i][j - 1].rgbtRed;
                g += temp[i][j - 1].rgbtGreen;
                b += temp[i][j - 1].rgbtBlue;
                counter++;
            }
            // Right pixel
            if (j + 1 <= width - 1)
            {
                r += temp[i][j + 1].rgbtRed;
                g += temp[i][j + 1].rgbtGreen;
                b += temp[i][j + 1].rgbtBlue;
                counter++;
            }

            // Calculate average of pixels forming 3x3 box
            image[i][j].rgbtRed = round(r / counter);
            image[i][j].rgbtGreen = round(g / counter);
            image[i][j].rgbtBlue = round(b / counter);
        }
    }
    return;
}
