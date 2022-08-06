#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float gray_color = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = gray_color;
            image[i][j].rgbtGreen = gray_color;
            image[i][j].rgbtBlue = gray_color;
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
            // Cores originais
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;

            // Cores sepia
            int sepia_red = round(.393 * red + .769 * green + .189 * blue);
            int sepia_green = round(.349 * red + .686 * green + .168 * blue);
            int sepia_blue = round(.272 * red + .534 * green + .131 * blue);

            if (i == 0 && j == 0)
            {
                printf("sepia rgb(%i, %i, %i)\n", sepia_red, sepia_green, sepia_blue);
            }

            // Troca as cores
            image[i][j].rgbtRed = sepia_red > 255 ? 255 : sepia_red;
            image[i][j].rgbtGreen = sepia_green > 255 ? 255 : sepia_green;
            image[i][j].rgbtBlue = sepia_blue > 255 ? 255 : sepia_blue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        RGBTRIPLE temp;
        for (int j = 0; j < (width / 2); j++)
        {
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // temp
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // percorre cada pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float red = 0;
            float green = 0;
            float blue = 0;
            int pixels = 0;

            // percorre os pixels ao redor do atual numa caixa 3x3
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= (j + 1); l++)
                {
                    if (k >= 0 && l >= 0 && k < height && l < width)
                    {
                        red += temp[k][l].rgbtRed;
                        green += temp[k][l].rgbtGreen;
                        blue += temp[k][l].rgbtBlue;
                        pixels++;

                        image[i][j].rgbtRed = (int)round(red / pixels);
                        image[i][j].rgbtGreen = (int)round(green / pixels);
                        image[i][j].rgbtBlue = (int)round(blue / pixels);
                    }
                }
            }
        }
    }
    return;
}
