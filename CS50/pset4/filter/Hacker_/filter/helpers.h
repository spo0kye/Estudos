#include "bmp.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]);

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width]);

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]);

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]);

//media of Red in pixel
int mediaR(int h, int w, int maxH, int maxW, RGBTRIPLE image[maxH][maxW]);

//media of Green in pixel
int mediaG(int h, int w, int maxH, int maxW, RGBTRIPLE image[maxH][maxW]);

//media of Blue in pixel
int mediaB(int h, int w, int maxH, int maxW, RGBTRIPLE image[maxH][maxW]);