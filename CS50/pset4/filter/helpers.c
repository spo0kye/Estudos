#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int media = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;
            image[i][j].rgbtBlue = media;
            image[i][j].rgbtGreen = media;
            image[i][j].rgbtRed = media;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int jpos = width / 2, jneg = jpos; jpos < width; jpos++, jneg--)
        {
            image[i][jpos].rgbtBlue = image[i][jneg].rgbtBlue;
            image[i][jpos].rgbtGreen = image[i][jneg].rgbtGreen;
            image[i][jpos].rgbtRed = image[i][jneg].rgbtRed;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    mediaB (height, width, image);
    mediaG (height, width, image);
    mediaR (height, width, image);
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 1; i < height; i++)
    {
        for (int j = 1; j < width; j++)
        {
            int somaR = 0, somaG = 0, somaB = 0;
            int media = 0;
            int squareX = 0, squareY = 0;

            //Soma na vertical
            for(int w = -1; w < 1; w++)
            {
                for(int h = -1; h < 1; h++)
                {
                    if(w == -1 || w == 1)
                    {
                        somaR += image[i+h][j+w].rgbtRed * w;
                        somaG += image[i+h][j+w].rgbtGreen * w;
                        somaB += image[i+h][j+w].rgbtBlue * w;
                    }

                    else
                    {
                        somaR += image[i+h][j+w].rgbtRed * 2;
                        somaG += image[i+h][j+w].rgbtGreen * 2;
                        somaB += image[i+h][j+w].rgbtBlue * 2;
                    }
                }
            squareY = sqrt (sqr (somaR + somaG + somaB));
            }

            //Soma na horizontal
            for(int h = -1; h < 1; h++)
            {
                for(int w = -1; w < 1; w++)
                {
                    if (w == -1 || w == 1)
                    {
                        somaR += (image[i+h][j+w].rgbtRed * h);
                        somaG += (image[i+h][j+w].rgbtGreen * h);
                        somaB += (image[i+h][j+w].rgbtBlue * h);
                    }

                    else
                    {
                        somaR += (image[i+h][j+w].rgbtRed * 2);
                        somaG += (image[i+h][j+w].rgbtGreen * 2);
                        somaB += (image[i+h][j+w].rgbtBlue * 2);
                    }
                }
            }
            squareX = sqrt(sqr(somaR + somaG + somaB));
            media = cbrt(squareX + squareY);

            if (media > 12)
            {
                image[i-1][j-1].rgbtRed = 150;
                image[i-1][j-1].rgbtGreen = 150;
                image[i-1][j-1].rgbtBlue = 150;
            }

            else
            {
                image[i-1][j-1].rgbtRed = 0;
                image[i-1][j-1].rgbtGreen = 0;
                image[i-1][j-1].rgbtBlue = 0;
            }
        }
    }
    return;
}


int mediaR(int h, int w, RGBTRIPLE image[h][w])
{
    int returnV = 0;
    for(int posY = 1; posY < h + 3; posY += 3)
    {
        for(int posX = 1; posX < w + 3; posX += 3)
        {
            returnV += image[posY][posX-1].rgbtRed + image[posY][posX+1].rgbtRed + image[posY][posX].rgbtRed;
        }
    }
    return returnV;
}

int mediaG(int h, int w, RGBTRIPLE image[h][w])
{
    int returnV = 0;
    for(int posY = 1; posY < h + 3; posY += 3)
    {
        for(int posX = 1; posX < w + 3; posX += 3)
        {
            returnV += image[posY][posX-1].rgbtGreen + image[posY][posX+1].rgbtGreen + image[posY][posX].rgbtGreen;
        }
    }
    return returnV;
}


int mediaB(int h, int w, RGBTRIPLE image[h][w])
{
    int returnV = 0;
    for(int posY = 1; posY < h + 3; posY += 3)
    {
        for(int posX = 1; posX < w + 3; posX += 3)
        {
            returnV += image[posY][posX-1].rgbtBlue + image[posY][posX+1].rgbtBlue + image[posY][posX].rgbtBlue;
        }
    }
    return returnV;
}

int sqr(int x)
{
    return pow (x, 2);
}