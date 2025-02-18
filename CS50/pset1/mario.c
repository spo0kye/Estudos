#include <stdio.h>
#include <string.h>


#define max 8


void repeat(char c, int vzs);


int main(void)
{
    int n;
    char buffer;
    do
    {
        printf("\rEnter a number between 1 and %i: ", max);
        buffer = fgetc(stdin);
        if(buffer < 48 || buffer > 57)
        {
            printf("\rERROR, %i is Not a Number\n", buffer);
            return 1;
        }
        n = buffer - '0';
    }
    while(n < 1 || n > max);

    for(int times = n - 1; times != 0; times--)
    {
        repeat(' ', times);
        repeat('#', n - times);
        printf("\n");
    }
    repeat('#', n);
    printf("\n");
    return 0;
}


void repeat(char c, int times)
{
    for(int i = 0; i < times; i++)
    {
        printf("%c", c);
    }
}