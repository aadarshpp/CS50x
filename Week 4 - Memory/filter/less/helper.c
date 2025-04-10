#include "helpers.h"

// Returns the nearest integer
int round_to_int(float n)
{
    int a = n;
    float f = n - a;
    if (f < 0.5)
        return a;
    else
        return a + 1;
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int r, c, red, green, blue;
    BYTE avg;

    for (r = 0; r < height; r++)
    {
        for (c = 0; c < width; c++)
        {
            red = image[r][c].rgbtRed;
            green = image[r][c].rgbtGreen;
            blue = image[r][c].rgbtBlue;

            avg = round_to_int((red + green + blue) / 3.0);

            image[r][c].rgbtRed = avg;
            image[r][c].rgbtGreen = avg;
            image[r][c].rgbtBlue = avg;
        }
    }
}

// Returns minimum of two float values
float min(float a, float b)
{
    return (a < b) ? a : b;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int r, c;
    RGBTRIPLE pixel;
    float sepiaRed, sepiaGreen, sepiaBlue;

    for (r = 0; r < height; r++)
    {
        for (c = 0; c < width; c++)
        {
            pixel = image[r][c];

            sepiaRed =
                min(255.0, .393 * pixel.rgbtRed + .769 * pixel.rgbtGreen + .189 * pixel.rgbtBlue);
            sepiaGreen =
                min(255.0, .349 * pixel.rgbtRed + .686 * pixel.rgbtGreen + .168 * pixel.rgbtBlue);
            sepiaBlue =
                min(255.0, .272 * pixel.rgbtRed + .534 * pixel.rgbtGreen + .131 * pixel.rgbtBlue);

            image[r][c].rgbtRed = round_to_int(sepiaRed);
            image[r][c].rgbtGreen = round_to_int(sepiaGreen);
            image[r][c].rgbtBlue = round_to_int(sepiaBlue);
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int r, c, d;
    RGBTRIPLE temp;

    for (r = 0; r < height; r++)
    {
        for (c = 0; c < width / 2; c++)
        {
            d = width - c - 1;
            temp = image[r][c];
            image[r][c] = image[r][d];
            image[r][d] = temp;
        }
    }
}

// Blurs one pixel using box average method
void blur_pixel(int height, int width, RGBTRIPLE image[height][width],
                RGBTRIPLE image_copy[height][width], int r, int c)
{
    int sum[] = {0, 0, 0};
    int count = 0;
    int directions[] = {-1, 0, 1};
    int i, j, dr, dc, nr, nc;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            dr = directions[i];
            dc = directions[j];
            nr = r + dr;
            nc = c + dc;

            // Skip out-of-bounds pixels
            if (nr < 0 || nr >= height || nc < 0 || nc >= width)
                continue;

            sum[0] += image_copy[nr][nc].rgbtRed;
            sum[1] += image_copy[nr][nc].rgbtGreen;
            sum[2] += image_copy[nr][nc].rgbtBlue;
            count++;
        }
    }

    if (count > 0)
    {
        image[r][c].rgbtRed = round_to_int((float) sum[0] / count);
        image[r][c].rgbtGreen = round_to_int((float) sum[1] / count);
        image[r][c].rgbtBlue = round_to_int((float) sum[2] / count);
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int r, c;
    RGBTRIPLE image_copy[height][width];

    for (r = 0; r < height; r++)
    {
        for (c = 0; c < width; c++)
        {
            image_copy[r][c] = image[r][c];
        }
    }

    for (r = 0; r < height; r++)
    {
        for (c = 0; c < width; c++)
        {
            blur_pixel(height, width, image, image_copy, r, c);
        }
    }
}
