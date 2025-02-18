#include "bmp.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]);

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]);

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]);

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]);

int mediaR(int h, int w, RGBTRIPLE image[h][w]);

int mediaG(int h, int w, RGBTRIPLE image[h][w]);

int mediaB(int h, int w, RGBTRIPLE image[h][w]);

int sqr(int x);