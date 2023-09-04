#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    int brightness;

    for (int h = 0; h < height; h++)
    {

        for (int w = 0; w < width; w++)
        {

            //Take the average value of each color of the pixel to determine the brightness
            brightness = round((image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed) / 3.0);

            //Apply the average brightness to each color in each pixel
            image[h][w].rgbtBlue = brightness;

            image[h][w].rgbtGreen = brightness;

            image[h][w].rgbtRed = brightness;

        }

    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE temp;

    for (int h = 0; h < height; h++)
    {

        for (int w = 0; w < (width / 2); w++)
        {

            //Temporaily save the value of the pixel
            temp = image[h][width - 1 - w];

            //Swap the pixels
            image[h][width - 1 - w] = image[h][w];

            image[h][w] = temp;

        }
    }

    return;

}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE paddedimage[height + 2][width + 2];
    float truefalse[height + 2][width + 2];

    //Creation of a padded image
    for (int h = 0; h < height + 2; h++)
    {

        for (int w = 0; w < width + 2; w++)
        {

            //The value of the pad is set to 0
            if (h == 0 || w == 0 || h == height + 1 || w == width + 1)
            {

                //Creation of the pad of padded image
                paddedimage[h][w].rgbtBlue = 0;

                paddedimage[h][w].rgbtGreen = 0;

                paddedimage[h][w].rgbtRed = 0;

                //Creation of the true/false grill: pad = 0 and image = 1
                truefalse[h][w] = 0.0;

            }

            else
            {

                //Importation of the original picture in the padded image
                paddedimage[h][w].rgbtBlue = image[h - 1][w - 1].rgbtBlue;

                paddedimage[h][w].rgbtGreen = image[h - 1][w - 1].rgbtGreen;

                paddedimage[h][w].rgbtRed = image[h - 1][w - 1].rgbtRed;

                //Creation of the true/false grill: pad = 0 and image = 1
                truefalse[h][w] = 1.0;

            }

        }

    }

    //Set the value of the grid g
    int g[3][3] =
    {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };

    //Determine the amount of cases that requires multiplication (*4 in corners, *6 on the edges and *9 elsewhere)
    for (int h = 1; h < height + 1; h++)
    {

        for (int w = 1; w < width + 1; w++)
        {
            //Set multiplication to 0
            float multiplication = 0;

            //Set all temporary g grids for each color to 0
            float tempgb = 0;
            float tempgg = 0;
            float tempgr = 0;

            for (int gh = 0; gh < 3; gh++)
            {

                for (int gw = 0; gw < 3; gw++)
                {

                    //Get the value of multiplication of 4, 6 or 9
                    multiplication += truefalse[h - 1 + gh][w - 1 + gw] * g[gh][gw];

                    //Multiply each pixel to their surrounding values
                    tempgb += paddedimage[h - 1 + gh][w - 1 + gw].rgbtBlue * g[gh][gw];
                    tempgg += paddedimage[h - 1 + gh][w - 1 + gw].rgbtGreen * g[gh][gw];
                    tempgr += paddedimage[h - 1 + gh][w - 1 + gw].rgbtRed * g[gh][gw];

                }

            }

            //Divide each total for each color by multiplication to get the average and set it back to the original image
            image[h - 1][w - 1].rgbtBlue = round(tempgb / multiplication);
            image[h - 1][w - 1].rgbtGreen = round(tempgg / multiplication);
            image[h - 1][w - 1].rgbtRed = round(tempgr / multiplication);

        }

    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE paddedimage[height + 2][width + 2];

    //Creation of a padded image
    for (int h = 0; h < height + 2; h++)
    {

        for (int w = 0; w < width + 2; w++)
        {

            //The value of the pad is set to 0
            if (h == 0 || w == 0 || h == height + 1 || w == width + 1)
            {

                paddedimage[h][w].rgbtBlue = 0;

                paddedimage[h][w].rgbtGreen = 0;

                paddedimage[h][w].rgbtRed = 0;

            }

            else
            {

                paddedimage[h][w].rgbtBlue = image[h - 1][w - 1].rgbtBlue;

                paddedimage[h][w].rgbtGreen = image[h - 1][w - 1].rgbtGreen;

                paddedimage[h][w].rgbtRed = image[h - 1][w - 1].rgbtRed;

            }

        }

    }

    //Set the value of the grid gx
    int gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    //Set the value of the grid gy
    int gy[3][3] =
    {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };

    for (int h = 1; h < height + 1; h++)
    {

        for (int w = 1; w < width + 1; w++)
        {

            //Set all temporary gx and gy grid for each color to 0
            float tempgxb = 0;
            float tempgxg = 0;
            float tempgxr = 0;
            float tempgyb = 0;
            float tempgyg = 0;
            float tempgyr = 0;

            for (int gh = 0; gh < 3; gh++)
            {

                for (int gw = 0; gw < 3; gw++)
                {

                    //Multiply the value to each grid to each pixels of paddedimage, for each color
                    tempgxb += paddedimage[h - 1 + gh][w - 1 + gw].rgbtBlue * gx[gh][gw];
                    tempgyb += paddedimage[h - 1 + gh][w - 1 + gw].rgbtBlue * gy[gh][gw];

                    tempgxg += paddedimage[h - 1 + gh][w - 1 + gw].rgbtGreen * gx[gh][gw];
                    tempgyg += paddedimage[h - 1 + gh][w - 1 + gw].rgbtGreen * gy[gh][gw];

                    tempgxr += paddedimage[h - 1 + gh][w - 1 + gw].rgbtRed * gx[gh][gw];
                    tempgyr += paddedimage[h - 1 + gh][w - 1 + gw].rgbtRed * gy[gh][gw];

                }

            }

            //Set the values back to the original image
            image[h - 1][w - 1].rgbtBlue = lround(fmin(sqrt(powf(tempgxb, 2) + powf(tempgyb, 2)), 255.0));
            image[h - 1][w - 1].rgbtGreen = lround(fmin(sqrt(powf(tempgxg, 2) + powf(tempgyg, 2)), 255.0));
            image[h - 1][w - 1].rgbtRed = lround(fmin(sqrt(powf(tempgxr, 2) + powf(tempgyr, 2)), 255.0));
        }

    }

    return;
}
