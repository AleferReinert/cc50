#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
// o new value pode ser somado ou subtraido por um número para obter um tom mais claro ou mais escuro
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float new_value;
    for (int row = 0; row < height; row++)
    {

        for (int column = 0; column < width; column++)
        {
            new_value = round((image[row][column].rgbtRed + image[row][column].rgbtGreen + image[row][column].rgbtBlue) / 3.00);
            if (new_value > 255)
            {
                new_value = 255;
            }
            else if (new_value < 0)
            {
                new_value = 0;
            }

            image[row][column].rgbtRed = new_value;
            image[row][column].rgbtGreen = new_value;
            image[row][column].rgbtBlue = new_value;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
