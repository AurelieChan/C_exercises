#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;

    do
    {
        //ask user to enter a height and save it as an integer
        height = get_int("Enter a height\n");

    }
    while (height < 1 || height > 8);


    // Print the pyramid if conditions are met.
    // To achive the left pyramid, the number of # is the same as c, which is the row number.
    // To allign it to the left side, we substract the number of # from the height and print spaces instead.
    for (int c = 1; c <= height; c++)
    {

        for (int r = 1; r <= height; r++)
        {

            if (r <= height - c)
            {

                printf(" ");

            }

            else
            {

                printf("#");

            }

        }

        //Print the space between both pyramid
        printf("  ");

        //Print the right pyramid
        for (int r = 1; r <= c; r++)
        {

            printf("#");

        }

        printf("\n");



    }

}
