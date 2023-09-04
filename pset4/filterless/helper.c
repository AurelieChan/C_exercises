#include "helpers.h"
#include <math.h>
#include <string.h>

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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    int sepiared, sepiagreen, sepiablue;

    for (int h = 0; h < height; h++)
    {

        for (int w = 0; w < width; w++)
        {

            //Determine the sepia value of pixel
            sepiared = lround(fmin((0.393 * image[h][w].rgbtRed) + (0.769 * image[h][w].rgbtGreen) + (0.189 * image[h][w].rgbtBlue), 255.0));

            sepiagreen = lround(fmin((0.349 * image[h][w].rgbtRed) + (0.686 * image[h][w].rgbtGreen) + (0.168 * image[h][w].rgbtBlue), 255.0));

            sepiablue = lround(fmin((0.272 * image[h][w].rgbtRed) + (0.534 * image[h][w].rgbtGreen) + (0.131 * image[h][w].rgbtBlue), 255.0));

            //Attribuate the sepia value back to each pixel
            image[h][w].rgbtRed = sepiared;

            image[h][w].rgbtGreen = sepiagreen;

            image[h][w].rgbtBlue = sepiablue;

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
    RGBTRIPLE imageblur[height][width];

    for (int h = 0; h < height ; h++)
    {

        for (int w = 0; w < width ; w++)
        {

            //Calculate the average value of the 4 pixels in each corner
            if (h == 0 && w == 0)
            {

                //Top left corner
                imageblur[0][0].rgbtBlue = round((image[h][w].rgbtBlue + image[h + 1][w].rgbtBlue + image[h][w + 1].rgbtBlue +
                                                  image[h + 1][w + 1].rgbtBlue) / 4.0);

                imageblur[0][0].rgbtRed = round((image[h][w].rgbtRed + image[h + 1][w].rgbtRed + image[h][w + 1].rgbtRed +
                                                 image[h + 1][w + 1].rgbtRed) / 4.0);

                imageblur[0][0].rgbtGreen = round((image[h][w].rgbtGreen + image[h + 1][w].rgbtGreen + image[h][w + 1].rgbtGreen +
                                                   image[h + 1][w + 1].rgbtGreen) / 4.0);

            }

            else if (h == 0 && w == (width - 1))
            {

                //Top right corner
                imageblur[0][width - 1].rgbtBlue = round((image[h][w].rgbtBlue + image[h][w - 1].rgbtBlue +
                                                   image[h + 1][w - 1].rgbtBlue + image[h + 1][w].rgbtBlue) / 4.0);

                imageblur[0][width - 1].rgbtRed = round((image[h][w].rgbtRed + image[h][w - 1].rgbtRed + image[h + 1][w - 1].rgbtRed +
                                                        image[h + 1][w].rgbtRed) / 4.0);

                imageblur[0][width - 1].rgbtGreen = round((image[h][w].rgbtGreen + image[h][w - 1].rgbtGreen +
                                                    image[h + 1][w - 1].rgbtGreen + image[h + 1][w].rgbtGreen) / 4.0);

            }

            else if (h == (height - 1) && w == 0)
            {

                //Bottom left corner
                imageblur[height - 1][0].rgbtBlue = round((image[h][w].rgbtBlue + image[h - 1][w].rgbtBlue +
                                                    image[h - 1][w + 1].rgbtBlue + image[h][w + 1].rgbtBlue) / 4.0);

                imageblur[height - 1][0].rgbtRed = round((image[h][w].rgbtRed + image[h - 1][w].rgbtRed +
                                                   image[h - 1][w + 1].rgbtRed + image[h][w + 1].rgbtRed) / 4.0);

                imageblur[height - 1][0].rgbtGreen = round((image[h][w].rgbtGreen + image[h - 1][w].rgbtGreen +
                                                     image[h - 1][w + 1].rgbtGreen + image[h][w + 1].rgbtGreen) / 4.0);

            }

            else if (h == (height - 1) && w == (width - 1))
            {

                //Bottom right corner
                imageblur[height - 1][width - 1].rgbtBlue = round((image[h][w].rgbtBlue + image[h][w - 1].rgbtBlue +
                        image[h - 1][w].rgbtBlue + image[h - 1][w - 1].rgbtBlue) / 4.0);

                imageblur[height - 1][width - 1].rgbtRed = round((image[h][w].rgbtRed + image[h][w - 1].rgbtRed +
                        image[h - 1][w].rgbtRed + image[h - 1][w - 1].rgbtRed) / 4.0);

                imageblur[height - 1][width - 1].rgbtGreen = round((image[h][w].rgbtGreen + image[h][w - 1].rgbtGreen +
                        image[h - 1][w].rgbtGreen + image[h - 1][w - 1].rgbtGreen) / 4.0);

            }

            //Calculate the average value of pixels in the border but not in the corners
            else if (h == 0 && w != 0 && w != (width - 1))
            {

                //Top line
                imageblur[0][w].rgbtBlue = round((image[h][w - 1].rgbtBlue + image[h][w].rgbtBlue + image[h][w + 1].rgbtBlue +
                                                  image[h + 1][w - 1].rgbtBlue + image[h + 1][w].rgbtBlue +
                                                  image[h + 1][w + 1].rgbtBlue) / 6.0);

                imageblur[0][w].rgbtRed = round((image[h][w - 1].rgbtRed + image[h][w].rgbtRed + image[h][w + 1].rgbtRed +
                                                 image[h + 1][w - 1].rgbtRed + image[h + 1][w].rgbtRed +
                                                 image[h + 1][w + 1].rgbtRed) / 6.0);

                imageblur[0][w].rgbtGreen = round((image[h][w - 1].rgbtGreen + image[h][w].rgbtGreen + image[h][w + 1].rgbtGreen +
                                                   image[h + 1][w - 1].rgbtGreen + image[h + 1][w].rgbtGreen +
                                                   image[h + 1][w + 1].rgbtGreen) / 6.0);

            }

            else if (h == (height - 1) && w != 0 && w != (width - 1))
            {

                //Bottom line
                imageblur[height - 1][w].rgbtBlue = round((image[h][w - 1].rgbtBlue + image[h][w].rgbtBlue + image[h][w + 1].rgbtBlue +
                                                    image[h - 1][w - 1].rgbtBlue + image[h - 1][w].rgbtBlue +
                                                    image[h - 1][w + 1].rgbtBlue) / 6.0);

                imageblur[height - 1][w].rgbtRed = round((image[h][w - 1].rgbtRed + image[h][w].rgbtRed + image[h][w + 1].rgbtRed +
                                                   image[h - 1][w - 1].rgbtRed + image[h - 1][w].rgbtRed +
                                                   image[h - 1][w + 1].rgbtRed) / 6.0);

                imageblur[height - 1][w].rgbtGreen = round((image[h][w - 1].rgbtGreen + image[h][w].rgbtGreen +
                                                     image[h][w + 1].rgbtGreen + image[h - 1][w - 1].rgbtGreen +
                                                     image[h - 1][w].rgbtGreen + image[h - 1][w + 1].rgbtGreen) / 6.0);
            }

            else if (w == 0 && h != 0 && h != (height - 1))
            {

                //Left line
                imageblur[h][0].rgbtBlue = round((image[h + 1][w].rgbtBlue + image[h][w].rgbtBlue + image[h - 1][w].rgbtBlue +
                                                  image[h + 1][w + 1].rgbtBlue + image[h][w + 1].rgbtBlue +
                                                  image[h - 1][w + 1].rgbtBlue) / 6.0);

                imageblur[h][0].rgbtRed = round((image[h + 1][w].rgbtRed + image[h][w].rgbtRed + image[h - 1][w].rgbtRed +
                                                 image[h + 1][w + 1].rgbtRed + image[h][w + 1].rgbtRed +
                                                 image[h - 1][w + 1].rgbtRed) / 6.0);

                imageblur[h][0].rgbtGreen = round((image[h + 1][w].rgbtGreen + image[h][w].rgbtGreen +
                                                   image[h - 1][w].rgbtGreen + image[h + 1][w + 1].rgbtGreen + image[h][w + 1].rgbtGreen +
                                                   image[h - 1][w + 1].rgbtGreen) / 6.0);

            }

            else if (w == (width - 1) && h != 0 && h != (height - 1))
            {

                //Right line
                imageblur[h][width - 1].rgbtBlue = round((image[h + 1][w].rgbtBlue + image[h][w].rgbtBlue +
                                                   image[h - 1][w].rgbtBlue + image[h + 1][w - 1].rgbtBlue +
                                                   image[h][w - 1].rgbtBlue + image[h - 1][w - 1].rgbtBlue) / 6.0);

                imageblur[h][width - 1].rgbtRed = round((image[h + 1][w].rgbtRed + image[h][w].rgbtRed + image[h - 1][w].rgbtRed +
                                                        image[h + 1][w - 1].rgbtRed + image[h][w - 1].rgbtRed +
                                                        image[h - 1][w - 1].rgbtRed) / 6.0);

                imageblur[h][width - 1].rgbtGreen = round((image[h + 1][w].rgbtGreen + image[h][w].rgbtGreen + image[h - 1][w].rgbtGreen +
                                                    image[h + 1][w - 1].rgbtGreen + image[h][w - 1].rgbtGreen +
                                                    image[h - 1][w - 1].rgbtGreen) / 6.0);

            }

            //Calculate the average value of the left over squares in the middle
            else
            {

                imageblur[h][w].rgbtBlue = round((image[h - 1][w - 1].rgbtBlue + image[h][w - 1].rgbtBlue + image[h + 1][w - 1].rgbtBlue +
                                                  image[h - 1][w].rgbtBlue + image[h][w].rgbtBlue + image[h + 1][w].rgbtBlue +
                                                  image[h - 1][w + 1].rgbtBlue + image[h][w + 1].rgbtBlue + image[h + 1][w + 1].rgbtBlue) / 9.0);

                imageblur[h][w].rgbtRed = round((image[h - 1][w - 1].rgbtRed + image[h][w - 1].rgbtRed + image[h + 1][w - 1].rgbtRed +
                                                 image[h - 1][w].rgbtRed + image[h][w].rgbtRed + image[h + 1][w].rgbtRed +
                                                 image[h - 1][w + 1].rgbtRed + image[h][w + 1].rgbtRed + image[h + 1][w + 1].rgbtRed) / 9.0);

                imageblur[h][w].rgbtGreen = round((image[h - 1][w - 1].rgbtGreen + image[h][w - 1].rgbtGreen + image[h + 1][w - 1].rgbtGreen +
                                                   image[h - 1][w].rgbtGreen + image[h][w].rgbtGreen + image[h + 1][w].rgbtGreen +
                                                   image[h - 1][w + 1].rgbtGreen + image[h][w + 1].rgbtGreen + image[h + 1][w + 1].rgbtGreen) / 9.0);

            }

        }

    }

    // void *memcpy(void *dest, const void *src, size_t n);
    memcpy(&image[0][0], &imageblur[0][0], sizeof(imageblur[0][0]) * height * width);
    //image = imageblur;

    return;
}
