#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

typedef struct node
{
    int number;
    struct node *next;
}
node;

int
main(int argc, char *argv[2])
{
    node *numbers = malloc(sizeof(node));
    numbers->number = get_int ("Digite um número: ");
    node *n2 = malloc(sizeof(node));
    if(n2 == NULL)
    {
        return 1;
    }

    //jump through nodes
    numbers->next = n2;
    n2->number = get_int("Digite um numero: ");
    for (node *cursor = numbers; cursor != NULL; cursor = cursor->next)
    {
        node* head = cursor;
        printf("%i\n", cursor->number);
        free(head);
    }
    
    return 0;
}
