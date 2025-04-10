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

// Returns the absolute value of a number
int abs(int n)
{
    return (n > 0) ? n : -n;
}

// Returns the integer nearest to the square root of a number
int nearest_sqrt(int n)
{
    if (n == 0)
        return 0;

    int l = 0;
    int r = n;
    int m;

    while (l <= r)
    {
        m = l + (r - l) / 2;
        if (m * m == n)
            return m;
        else if (m * m > n)
            r = m - 1;
        else
            l = m + 1;
    }

    if (abs(l * l - n) <= abs(r * r - n))
        return l;
    else
        return r;
}

// Return minimum of two integers
int min(int a, int b)
{
    return (a < b) ? a : b;
}

// Applies the soble operator a pixel
void apply_soble_oprator(int height, int width, RGBTRIPLE image[height][width],
                         RGBTRIPLE image_copy[height][width], int r, int c)
{
    int Gx[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int Gy[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};

    int Sx[] = {0, 0, 0};
    int Sy[] = {0, 0, 0};
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

            Sx[0] += image_copy[nr][nc].rgbtRed * Gx[i * 3 + j];
            Sx[1] += image_copy[nr][nc].rgbtGreen * Gx[i * 3 + j];
            Sx[2] += image_copy[nr][nc].rgbtBlue * Gx[i * 3 + j];

            Sy[0] += image_copy[nr][nc].rgbtRed * Gy[i * 3 + j];
            Sy[1] += image_copy[nr][nc].rgbtGreen * Gy[i * 3 + j];
            Sy[2] += image_copy[nr][nc].rgbtBlue * Gy[i * 3 + j];
        }
    }

    image[r][c].rgbtRed = min(255, nearest_sqrt(Sx[0] * Sx[0] + Sy[0] * Sy[0]));
    image[r][c].rgbtGreen = min(255, nearest_sqrt(Sx[1] * Sx[1] + Sy[1] * Sy[1]));
    image[r][c].rgbtBlue = min(255, nearest_sqrt(Sx[2] * Sx[2] + Sy[2] * Sy[2]));
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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
            apply_soble_oprator(height, width, image, image_copy, r, c);
        }
    }
}
