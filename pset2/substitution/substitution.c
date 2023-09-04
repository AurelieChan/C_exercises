#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, string argv[])
{

    int k, exitcode, count;

    string pt;

    string ct;

    //Check if user entered any input
    if (argc == 2)
    {

        //Check if input has 26 letters
        if (strlen(argv[1]) != 26)
        {

            printf("The key must contain 26 alphabetic characters\n");

            return 1;

        }

        else
        {

            //Check if user entered a valid input
            for (int i = 0; i < strlen(argv[1]); i++)
            {

                //Check if input contains only letters
                if (!isalpha(argv[1][i]))
                {

                    printf("The key must contain only alphabetic characters\n");

                    return 1;

                }

                //Convert each character i into lower case
                if ((isupper(argv[1][i])))
                {

                    argv[1][i] = argv[1][i] + 32;

                }

                //Check for repeated characters
                count = 1;

                for (int j = i + 1; j < strlen(argv[1]); j++)
                {

                    //Convert each character j into lower case
                    if (isupper(argv[1][j]))
                    {

                        argv[1][j] = argv[1][j] + 32;

                    }

                    if (argv[1][i] == argv[1][j])
                    {

                        count++;

                    }

                }

                if (count > 1)
                {

                    printf("The key must not contain repeated characters\n");

                    return 1;

                }

            } // for loop

        }  // else

    }

    else
    {

        printf("Usage: ./substitution key\n");

        return 1;

    }

    //Prompt user for plaintext
    pt = get_string("plaintext: ");

    ct = pt;

    for (int i = 0; i < strlen(pt); i++)
    {

        //Get lower cases and convert them into ciphertext
        if ((islower((int) pt[i])))
        {

            ct[i] = argv[1][pt[i] - 97];

        }

        //Get upper cases and convert them into ciphertext
        if ((isupper((int) pt[i])))
        {

            ct[i] = (argv[1][pt[i] - 65]) - 32;

        }

    }

    //Print ciphertext
    printf("ciphertext: %s\n", ct);

    return 0;

}



