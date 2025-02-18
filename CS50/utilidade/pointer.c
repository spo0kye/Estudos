#include <stdio.h>
#include <cs50.h>

void swap(int *j, int *k);

int
main(void)
{
    int A = 1;
    int B = 2;
    swap(&A, &B);
    printf ("%i %i\n", A, B);
}

void
swap(int *j, int *k)
{
    int tmp = *j;
    *j = *k;
    *k = tmp;
}