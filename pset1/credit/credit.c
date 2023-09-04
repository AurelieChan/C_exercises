#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    int digit, total, counter;
    long card, tempcard, first;

    //Prompt user for a card number. Must be an integer with no hyphen or symbol.
    card = get_long("Enter a card number\n");

    printf("Number: %li\n", card);

    //Calculate checksum:
    //Multiply every other digit by 2, starting with the second-to-last digit ans add them together
    tempcard = card;

    tempcard = tempcard / 10;

    digit = (tempcard % 10) * 2;

    counter = 0;

    //If the product is > 9, then add the products' digit together
    if (digit > 9)
    {

        digit = (digit % 10) + digit / 10;

    }

    total = digit;

    do
    {

        tempcard = tempcard / 100;

        digit = (tempcard % 10) * 2;

        //If the product is > 9, then add the products' digit together
        if (digit > 9)
        {

            digit = (digit % 10) + digit / 10;

        }

        total += digit;

        counter ++;

    }
    while (tempcard >= 1);

    //Add the sum to the sum of digits that were not multiplied by 2
    tempcard = card;

    do
    {

        digit = (tempcard % 10);

        tempcard = tempcard / 100;

        total += digit;

        counter ++;

    }
    while (tempcard >= 1);

    //If the total's last digit is 0, it passes that first step
    if (total % 10 == 0)
    
    //Check for card length and starting digits and print card name or if it is an invalid number
    {
        
        //Check conditions for AMEX
        first = card / pow(10, counter - 2);
        
        if (counter == 15 && (first == 34 || first == 37))
        {
                
            printf("AMEX\n");
              
        }

        //Check conditions for Mastercard
        else if (counter == 16 && (first >= 51 && first <= 55))
        {
                
            printf("MASTERCARD\n");
              
        }

        //Check conditions for VISA
        else if ((counter == 13 || counter == 16) && (first / 10 == 4))
        {

            printf("VISA\n");

        }
        
        else
        {

            printf("INVALID\n");

        }


    }

    else
    {

        printf("INVALID\n");

    }

}