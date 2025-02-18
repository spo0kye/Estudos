// See if a credit card number could exist

#include <stdio.h>
#include "cs50.h"


bool verify(int n[], int count);


int main(void)
{
    long incard = get_long("Enter the credit card number: ");
    int outcard[16];
    int count = 0;
    while (incard)
    {
        outcard[count] = incard % 10;
        incard /= 10;
        count++;
    }
    
    if (verify(outcard, count) == true)
        printf("\rCredit Card number valid\n");

    else
        printf("\rInvalid Credit Card number\n");

   return 0;
}


bool verify(int n[], int count)
{
    int times = 1;
    int n2 = 0;
    while(times < count)
    {
        n[times] *= 2;
        if (n[times] > 10)
        {
            n2 += n[times] % 10;
            n2 += n[times] / 10;
        }

        if (times > 1)
            n2 += n[times];

        else
        {
            n2 = n[times];
            times += 2;
        }

    }

    while (count > 0)
    {
        n2 += n[count];
        count--;
    }

    if (n2 % 10 != 0)
        return false;

    else
        return true;
}