#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float cash;
    int coins = 0;
    int cents;

    do
    {
        //Prompt user for an amount of change and save it as a float
        cash = get_float("Enter an amount of change\n");

    }
    while (cash <= 0);

    printf("Change owed: %.2f\n", cash);

    //Store the amount in a cent value
    cents = round(cash * 100);

    //Divide the amount by the value of each coins to know how many of them to give
    //Use the reminder to get the result with smaller coins
    if (cents >= 25)
    {

        coins += cents / 25;

        cents %= 25;

    }

    if (cents >= 10)
    {

        coins += cents / 10;

        cents %= 10;

    }

    if (cents >= 5)
    {

        coins += cents / 5;

        cents %= 5;

    }

    coins += cents;

    //Print the number of coins to be given
    printf("%i\n", coins);
}
