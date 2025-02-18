#include <stdio.h>
#include <cs50.h>

int start;
int end;


int
main(void)
{
    do
    {
        start = get_int("\rDigite a quantidade inicial: ");
    }
    while (start < 1);

    do
    {
        end = get_int("\rDigite a quantidade final: ");
    }
    while (end <= start);
    int peryear = (start / 3) - (start / 4);
    int count = 0;
    do
    {
        start += peryear;
        count++;
    }
    while (start < end);
    if (count > 1)
        printf("%i anos \n", count);
    else
        printf("%i ano\n", count);
    return 0;
}