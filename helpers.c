#include "helpers.h"
#include <math.h>
#include <stdlib.h>

int maximum(int h);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h <= (height - 1); h++)
    {
        for (int w = 0; w <= (width - 1); w++)
        {
            int average = round((image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed) / 3.0);
            image[h][w].rgbtBlue = average;
            image[h][w].rgbtGreen = average;
            image[h][w].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h <= (height - 1); h++)
    {
        for (int w = 0; w <= (width - 1); w++)
        {
            int sepiaRed = round(.393 * image[h][w].rgbtRed + .769 * image[h][w].rgbtGreen + .189 * image[h][w].rgbtBlue);
            int sepiaGreen = round(.349 * image[h][w].rgbtRed + .686 * image[h][w].rgbtGreen + .168 * image[h][w].rgbtBlue);
            int sepiaBlue = round(.272 * image[h][w].rgbtRed + .534 * image[h][w].rgbtGreen + .131 * image[h][w].rgbtBlue);
            image[h][w].rgbtRed = maximum(sepiaRed);
            image[h][w].rgbtGreen = maximum(sepiaGreen);
            image[h][w].rgbtBlue = maximum(sepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h <= (height - 1); h++)
    {
        int n = 0;
        for (int w = 0; w <= (width / 2) - 1; w++)
        {
            n++;
            RGBTRIPLE initialByte = image[h][w];
            image[h][w] = image[h][width - n];
            image[h][width - n] = initialByte;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            copy[h][w].rgbtRed = image[h][w].rgbtRed;
            copy[h][w].rgbtGreen = image[h][w].rgbtGreen;
            copy[h][w].rgbtBlue = image[h][w].rgbtBlue;
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            if (h == 0)
            {
                //first corner in the first row
                if (w == 0)
                {
                    //take the average of each color in the surrounding pixels including the main pixel
                    image[h][w].rgbtRed = round((copy[0][0].rgbtRed + copy[0][1].rgbtRed + copy[1][0].rgbtRed + copy[1][1].rgbtRed) / 4.0);
                    image[h][w].rgbtGreen = round((copy[0][0].rgbtGreen + copy[0][1].rgbtGreen + copy[1][0].rgbtGreen + copy[1][1].rgbtGreen) / 4.0);
                    image[h][w].rgbtBlue = round((copy[0][0].rgbtBlue + copy[0][1].rgbtBlue + copy[1][0].rgbtBlue + copy[1][1].rgbtBlue) / 4.0);
                }
                //second corner in the first row
                else if (w == (width - 1))
                {
                    //take the average of each color in the surrounding pixels including the main pixel
                    image[h][w].rgbtRed = round((copy[0][width - 2].rgbtRed + copy[0][width - 1].rgbtRed + copy[1][width - 2].rgbtRed + copy[1][width -
                                                 1].rgbtRed) / 4.0);
                    image[h][w].rgbtGreen = round((copy[0][width - 2].rgbtGreen + copy[0][width - 1].rgbtGreen + copy[1][width - 2].rgbtGreen +
                                                   copy[1][ width - 1].rgbtGreen) / 4.0);
                    image[h][w].rgbtBlue = round((copy[0][width - 2].rgbtBlue + copy[0][width - 1].rgbtBlue + copy[1][width - 2].rgbtBlue +
                                                  copy[1][width - 1].rgbtBlue) / 4.0);
                }
                //edges of the first row
                else
                {
                    int totalRed = 0;
                    int totalGreen = 0;
                    int totalBlue = 0;
                    for (int i = 0; i <= 1; i++)
                    {
                        for (int j = (w - 1); j <= (w + 1); j++)
                        {
                            totalRed += copy[i][j].rgbtRed;
                            totalGreen += copy[i][j].rgbtGreen;
                            totalBlue += copy[i][j].rgbtBlue;
                        }
                    }
                    image[h][w].rgbtRed = round(totalRed / 6.0);
                    image[h][w].rgbtGreen = round(totalGreen / 6.0);
                    image[h][w].rgbtBlue = round(totalBlue / 6.0);
                }
            }
            // last row
            else if (h == (height - 1))
            {
                // first corner on last row
                if (w == 0)
                {
                    //take the average of each color in the surrounding pixels including the main pixel
                    image[h][w].rgbtRed = round((copy[height - 2][0].rgbtRed + copy[height - 2][1].rgbtRed + copy[height - 1][0].rgbtRed + copy[height -
                                                 1][1].rgbtRed) / 4.0);
                    image[h][w].rgbtGreen = round((copy[height - 2][0].rgbtGreen + copy[height - 2][1].rgbtGreen + copy[height - 1][0].rgbtGreen +
                                                   copy[height - 1][1].rgbtGreen) / 4.0);
                    image[h][w].rgbtBlue = round((copy[height - 2][0].rgbtBlue + copy[height - 2][1].rgbtBlue + copy[height - 1][0].rgbtBlue +
                                                  copy[height - 1][1].rgbtBlue) / 4.0);
                }
                //second corner on the last row
                else if (w == (width - 1))
                {
                    //take the average of each color in the surrounding pixels including the main pixel
                    image[h][w].rgbtRed = round((copy[height - 2][width - 2].rgbtRed + copy[height - 2][width - 1].rgbtRed + copy[height - 1][width -
                                                 2].rgbtRed + copy[height - 1][width - 1].rgbtRed) / 4.0);
                    image[h][w].rgbtGreen = round((copy[height - 2][width - 2].rgbtGreen + copy[height - 2][width - 1].rgbtGreen + copy[height -
                                                   1][width - 2].rgbtGreen + copy[height - 1][width - 1].rgbtGreen) / 4.0);
                    image[h][w].rgbtBlue = round((copy[height - 2][width - 2].rgbtBlue + copy[height - 2][width - 1].rgbtBlue + copy[height - 1][width -
                                                  2].rgbtBlue + copy[height - 1][width - 1].rgbtBlue) / 4.0);
                }
                //edges of the last row
                else
                {
                    int totalRed = 0;
                    int totalGreen = 0;
                    int totalBlue = 0;
                    for (int i = (height - 2); i <= (height - 1); i++)
                    {
                        for (int j = (w - 1); j <= (w + 1); j++)
                        {
                            totalRed += copy[i][j].rgbtRed;
                            totalGreen += copy[i][j].rgbtGreen;
                            totalBlue += copy[i][j].rgbtBlue;
                        }
                    }
                    image[h][w].rgbtRed = round(totalRed / 6.0);
                    image[h][w].rgbtGreen = round(totalGreen / 6.0);
                    image[h][w].rgbtBlue = round(totalBlue / 6.0);
                }
            }
            else
            {
                //left edges
                if (w == 0)
                {
                    int totalRed = 0;
                    int totalGreen = 0;
                    int totalBlue = 0;
                    for (int i = (h - 1); i <= (h + 1); i++)
                    {
                        for (int j = 0; j <= 1; j++)
                        {
                            totalRed += copy[i][j].rgbtRed;
                            totalGreen += copy[i][j].rgbtGreen;
                            totalBlue += copy[i][j].rgbtBlue;
                        }
                    }
                    image[h][w].rgbtRed = round(totalRed / 6.0);
                    image[h][w].rgbtGreen = round(totalGreen / 6.0);
                    image[h][w].rgbtBlue = round(totalBlue / 6.0);
                }
                //right edges
                else if (w == (width - 1))
                {
                    int totalRed = 0;
                    int totalGreen = 0;
                    int totalBlue = 0;
                    for (int i = (h - 1); i <= (h + 1); i++)
                    {
                        for (int j = (width - 2); j <= (width - 1); j++)
                        {
                            totalRed += copy[i][j].rgbtRed;
                            totalGreen += copy[i][j].rgbtGreen;
                            totalBlue += copy[i][j].rgbtBlue;
                        }
                    }
                    image[h][w].rgbtRed = round(totalRed / 6.0);
                    image[h][w].rgbtGreen = round(totalGreen / 6.0);
                    image[h][w].rgbtBlue = round(totalBlue / 6.0);
                }
                //center
                else
                {
                    int totalRed = 0;
                    int totalGreen = 0;
                    int totalBlue = 0;
                    for (int i = (h - 1); i <= (h + 1); i++)
                    {
                        for (int j = (w - 1); j <= (w + 1); j++)
                        {
                            totalRed += copy[i][j].rgbtRed;
                            totalGreen += copy[i][j].rgbtGreen;
                            totalBlue += copy[i][j].rgbtBlue;
                        }
                    }
                    image[h][w].rgbtRed = round(totalRed / 9.0);
                    image[h][w].rgbtGreen = round(totalGreen / 9.0);
                    image[h][w].rgbtBlue = round(totalBlue / 9.0);
                }
            }
        }
    }
    return;
}

int maximum(int h)
{
    if (h > 255)
    {
        return 255;
    }
    else
    {
        return h;
    }
}
