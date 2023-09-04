#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, string argv[])
{

    int k, exitcode;
    string pt;

    //Check if the user entered a correct input
    if (argc == 2)
    {
        //Check input contains only digits
        for (int i = 0; i < strlen(argv[1]); i++)
        {

            //If the imput is incorrect exit to return 1
            if (!isdigit(argv[1][i]))
            {

                exitcode = 1;

            }

        }

        //convert the string into an integer
        k = atoi(argv[1]);

        //check if user entered a valid integer
        if (k > 0 && exitcode != 1)
        {

            //Promp user for a plaintext
            pt = get_string("plaintext: ");

            //Check how many characters in the string (strlen(text))
            int length = strlen(pt);

            //Convert ASCII to alphabetical index
            for (int i = 0; i < length; i++)
            {

                //Get lower cases
                if ((islower((int) pt[i])))
                {

                    //Convert lower cases into ciphertext
                    pt[i] = (((int) pt[i] - 96 + k) % 26) + 96;

                }

                //Get upper cases
                if ((isupper((int)pt[i])))
                {

                    //Convert upper cases into ciphertext
                    pt[i] = (((int) pt[i] - 64 + k) % 26) + 64;

                }

            }

            //Print the ciphertext
            printf("ciphertext: %s\n", pt);

            return 0;

        }

    }

    printf("Usage: ./caesar key\n");

    return 1;

}