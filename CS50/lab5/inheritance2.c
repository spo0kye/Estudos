#include <stdio.h>
#include <time.h>
#include <stdlib.h>


#define GENERATIONS 3
#define INDENTATION 4


typedef struct person
{
    struct person *parents[2];
    char alleles[2];
} person;


person *create_family(int generation);
person *print_family(person *p, int generation);
char random_allele();
void free_family(person *p);


int main()
{
    srand(0);
    person *p = create_family(GENERATIONS);
    (void)print_family(p, 0);
    free_family(p);
}


person *create_family(int generation)
{
    person *p = malloc(sizeof(person));

    if(generation > 1)
    {
        p->parents[0] = create_family(generation - 1);
        p->parents[1] = create_family(generation - 1);
    }

    else
    {
        p->parents[0] = NULL;
        p->parents[1] = NULL;
    }

    p->alleles[0] = random_allele();
    p->alleles[1] = random_allele();
    return p;
}


char random_allele()
{
    int RandomNumber = rand() % 3;
    switch(RandomNumber)
    {
        case 0:
            return 'A';

        case 1:
            return 'B';

        case 2:
            return 'O';

        default:
            return 'E';
    }
}


person *print_family(person *p, int generation)
{
    if(p != NULL)
    {
        for (int i = 0; i < generation * INDENTATION; i++)
        {
            printf(" ");
        }

        printf("Generation: %i, Blood Type: %c%c\n", generation, p->alleles[0], p->alleles[1]);
        (void)print_family(p->parents[0], generation + 1);
        (void)print_family(p->parents[1], generation + 1);
    }

    return NULL;
}


void free_family(person *p)
{
    if(p->parents[0] != NULL)
    {
        free_family(p->parents[0]);
        free_family(p->parents[1]);
    }

    free(p);
    return;
}