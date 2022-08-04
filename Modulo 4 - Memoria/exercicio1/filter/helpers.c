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
    for (int row = 0; row < height; row++)
    {
        RGBTRIPLE tmp;

        int start = 0;
        int end = width - 1;

        while (start < end)
        {
            tmp = image[row][start];
            image[row][start] = image[row][end];
            image[row][end] = tmp;
            start++;
            end--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Cópia da imagem para usar no cálculo do blur
    RGBTRIPLE copy[height][width];
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            copy[row][column] = image[row][column];
        }
    }

    // Blur
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            float qtd_pixels = 0; // Quantidade de pixels existentes
            float r = 0;          // Soma de vermelho dos pixels existentes
            float g = 0;          // Soma de verde dos pixels existentes
            float b = 0;          // Soma de azul dos pixels existentes

            /*  Verifica cada pixel ao redor do pixel atual (como uma caixa 3x3).
                Se o pixel estiver dentro dos limites da imagem:
                    Atualiza a quantidade de pixels
                    Pega a quantidade de cada cor e adiciona nas variáveis acima para fazer a soma
            */
            for (int box_row = row - 1; box_row <= (row + 1); box_row++)
            {
                for (int box_column = column - 1; box_column <= (column + 1); box_column++)
                {
                    if (box_row >= 0 && box_column >= 0 && box_row < height && box_column < width)
                    {
                        qtd_pixels++;
                        r += copy[box_row][box_column].rgbtRed;
                        g += copy[box_row][box_column].rgbtGreen;
                        b += copy[box_row][box_column].rgbtBlue;
                    }
                }
            }
            // Atualiza o pixel atual com os novos valores
            image[row][column].rgbtRed = round(r / qtd_pixels);
            image[row][column].rgbtGreen = round(g / qtd_pixels);
            image[row][column].rgbtBlue = round(b / qtd_pixels);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int r_x = 0;
            int g_x = 0;
            int b_x = 0;
            int r_y = 0;
            int g_y = 0;
            int b_y = 0;

            for (int x = 0; x < 3; x++)
            {
                for (int y = 0; y < 3; y++)
                {
                    // Pixels válidos
                    if (i - 1 + x < 0 || i - 1 + x > height - 1 || j - 1 + y < 0 || j - 1 + y > width - 1)
                    {
                        continue;
                    }
                    r_x += image[i - 1 + x][j - 1 + y].rgbtRed * gx[x][y];
                    g_x += image[i - 1 + x][j - 1 + y].rgbtGreen * gx[x][y];
                    b_x += image[i - 1 + x][j - 1 + y].rgbtBlue * gx[x][y];
                    r_y += image[i - 1 + x][j - 1 + y].rgbtRed * gy[x][y];
                    g_y += image[i - 1 + x][j - 1 + y].rgbtGreen * gy[x][y];
                    b_y += image[i - 1 + x][j - 1 + y].rgbtBlue * gy[x][y];
                }
            }
            int red = round(sqrt((r_x * r_x) + (r_y * r_y)));
            int green = round(sqrt((g_x * g_x) + (g_y * g_y)));
            int blue = round(sqrt((b_x * b_x) + (b_y * b_y)));

            temp[i][j].rgbtRed = red > 255 ? 255 : red;
            temp[i][j].rgbtGreen = green > 255 ? 255 : green;
            temp[i][j].rgbtBlue = blue > 255 ? 255 : blue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }
    return;
}
