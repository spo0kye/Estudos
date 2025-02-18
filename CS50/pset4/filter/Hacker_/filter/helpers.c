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
            int media = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;
            image[i][j].rgbtBlue = media;
            image[i][j].rgbtGreen = media;
            image[i][j].rgbtRed = media;
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
            int sepiaRed = (0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) + (0.189 * image[i][j].rgbtBlue);
            int sepiaGreen = (0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) + (0.168 * image[i][j].rgbtBlue);
            int sepiaBlue = (0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) + (0.131 * image[i][j].rgbtBlue);
            if (sepiaRed > 255)
                sepiaRed = 255;

            if (sepiaBlue > 255)
                sepiaBlue = 255;

            if (sepiaGreen > 255)
                sepiaGreen = 255;

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
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
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = mediaB (i, j, height, width, image);
            image[i][j].rgbtGreen = mediaG (i, j, height, width, image);
            image[i][j].rgbtRed = mediaR (i, j, height, width, image);
        }
    }
    return;
}

int mediaR(int h, int w, int maxH, int maxW, RGBTRIPLE image[maxH][maxW])
{
    if(h == 0)
    {
        if(w == 0)
            return (image[h][w].rgbtRed + image[h+1][w].rgbtRed + image[h][w+1].rgbtRed + image[h+1][w+1].rgbtRed) / 4;

        else
            return (image[h][w-1].rgbtRed + image[h][w].rgbtRed + image[h][w+1].rgbtRed + image[h+1][w-1].rgbtRed + image[h+1][w].rgbtRed + image[h+1][w+1].rgbtRed) / 6;
    }

    else if(w == 0)
            return (image[h-1][w].rgbtRed + image[h][w].rgbtRed + image[h+1][w].rgbtRed + image[h-1][w+1].rgbtRed + image[h][w+1].rgbtRed + image[h+1][w+1].rgbtRed) / 6;

    else if(h == maxH)
    {
        if(w == maxW)
            return (image[h-1][w-1].rgbtRed + image[h-1][w].rgbtRed + image[h][w-1].rgbtRed + image[h][w].rgbtRed) / 4;

        else
            return (image[h-1][w-1].rgbtRed + image[h-1][w].rgbtRed + image[h-1][w+1].rgbtRed + image[h][w-1].rgbtRed + image[h][w].rgbtRed + image[h][w+1].rgbtRed) / 6;
    }

    else if (w == maxW)
        return (image[h-1][w-1].rgbtRed + image[h-1][w].rgbtRed + image[h][w-1].rgbtRed + image[h+1][w-1].rgbtRed + image[h+1][w].rgbtRed) / 4;

    else
        return (image[h-1][w-1].rgbtRed + image[h-1][w].rgbtRed + image[h-1][w+1].rgbtRed + image[h][w-1].rgbtRed + image[h][w].rgbtRed + image[h][w+1].rgbtRed + image[h+1][w-1].rgbtRed + image[h+1][w].rgbtRed + image[h+1][w+1].rgbtRed) / 9;
}

int mediaG(int h, int w, int maxH, int maxW, RGBTRIPLE image[maxH][maxW])
{
    if(h == 0)
    {
        if(w == 0)
            return (image[h][w].rgbtGreen + image[h+1][w].rgbtGreen + image[h][w+1].rgbtGreen + image[h+1][w+1].rgbtGreen) / 4;

        else
            return (image[h][w-1].rgbtGreen + image[h][w].rgbtGreen + image[h][w+1].rgbtGreen + image[h+1][w-1].rgbtGreen + image[h+1][w].rgbtGreen + image[h+1][w+1].rgbtGreen) / 6;
    }

    else if(w == 0)
            return (image[h-1][w].rgbtGreen + image[h][w].rgbtGreen + image[h+1][w].rgbtGreen + image[h-1][w+1].rgbtGreen + image[h][w+1].rgbtGreen + image[h+1][w+1].rgbtGreen) / 6;

    else if(h == maxH)
    {
        if(w == maxW)
            return (image[h-1][w-1].rgbtGreen + image[h-1][w].rgbtGreen + image[h][w-1].rgbtGreen + image[h][w].rgbtGreen) / 4;

        else
            return (image[h-1][w-1].rgbtGreen + image[h-1][w].rgbtGreen + image[h-1][w+1].rgbtGreen + image[h][w-1].rgbtGreen + image[h][w].rgbtGreen + image[h][w+1].rgbtGreen) / 6;
    }

    else if (w == maxW)
        return (image[h-1][w-1].rgbtGreen + image[h-1][w].rgbtGreen + image[h][w-1].rgbtGreen + image[h+1][w-1].rgbtGreen + image[h+1][w].rgbtGreen) / 4;

    else
        return (image[h-1][w-1].rgbtGreen + image[h-1][w].rgbtGreen + image[h-1][w+1].rgbtGreen + image[h][w-1].rgbtGreen + image[h][w].rgbtGreen + image[h][w+1].rgbtGreen + image[h+1][w-1].rgbtGreen + image[h+1][w].rgbtGreen + image[h+1][w+1].rgbtGreen) / 9;
}

int mediaB(int h, int w, int maxH, int maxW, RGBTRIPLE image[maxH][maxW])
{
    if(h == 0)
    {
        if(w == 0)
            return (image[h][w].rgbtBlue + image[h+1][w].rgbtBlue + image[h][w+1].rgbtBlue + image[h+1][w+1].rgbtBlue) / 4;

        else
            return (image[h][w-1].rgbtBlue + image[h][w].rgbtBlue + image[h][w+1].rgbtBlue + image[h+1][w-1].rgbtBlue + image[h+1][w].rgbtBlue + image[h+1][w+1].rgbtBlue) / 6;
    }

    else if(w == 0)
            return (image[h-1][w].rgbtBlue + image[h][w].rgbtBlue + image[h+1][w].rgbtBlue + image[h-1][w+1].rgbtBlue + image[h][w+1].rgbtBlue + image[h+1][w+1].rgbtBlue) / 6;

    else if(h == maxH)
    {
        if(w == maxW)
            return (image[h-1][w-1].rgbtBlue + image[h-1][w].rgbtBlue + image[h][w-1].rgbtBlue + image[h][w].rgbtBlue) / 4;

        else
            return (image[h-1][w-1].rgbtBlue + image[h-1][w].rgbtBlue + image[h-1][w+1].rgbtBlue + image[h][w-1].rgbtBlue + image[h][w].rgbtBlue + image[h][w+1].rgbtBlue) / 6;
    }

    else if (w == maxW)
        return (image[h-1][w-1].rgbtBlue + image[h-1][w].rgbtBlue + image[h][w-1].rgbtBlue + image[h+1][w-1].rgbtBlue + image[h+1][w].rgbtBlue) / 4;

    else
        return (image[h-1][w-1].rgbtBlue + image[h-1][w].rgbtBlue + image[h-1][w+1].rgbtBlue + image[h][w-1].rgbtBlue + image[h][w].rgbtBlue + image[h][w+1].rgbtBlue + image[h+1][w-1].rgbtBlue + image[h+1][w].rgbtBlue + image[h+1][w+1].rgbtBlue) / 9;
}