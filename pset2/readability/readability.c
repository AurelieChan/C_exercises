#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(void)
{
    string text;

    int valchar = 0;
    int space = 0;
    int sent = 0;
    int word = 0;

    //Prompt user to enter a text
    text = get_string("Text: ");

    //Get the amount of letters
    int length = strlen(text);

    for (int i = 0; i < length; i++)
    {

        //Get upper cases
        if ((int) text[i] >= 65 && text[i] <= 90)
        {

            valchar += 1;

        }

        //Get lower cases
        else if ((int) text[i] >= 97 && text[i] <= 122)
        {

            valchar += 1;

        }

        //Get spaces
        else if ((int) text[i] == 32)
        {

            space += 1;

        }

        //Get punctuations marking end of a sentence
        else if ((int) text[i] == 33 || (int) text[i] == 46 || (int) text[i] == 63)
        {

            sent += 1;

        }


    }

    word = (space + 1);

    //Implementing the formula
    float L = (float) valchar / ((float)word / 100);
    
    float S = (float) sent / ((float) word / 100);

    float index = 0.0588 * L - 0.296 * S - 15.8;
    
    if (round(index) < 1)
    {
      
        printf("Before Grade 1\n");
      
    }
    
    else if (round(index) > 16)
    {
      
        printf("Grade 16+\n");
      
    }
    
    else
    {

        printf("Grade %.f\n", round(index));
      
    }

}