#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>

typedef uint8_t BYTE;

int
main(void)
{
    FILE *file = fopen ("phonebook.csv", "a");
    if (file == NULL)
    {
         return 1;
    }
    char *nome = get_string ("\rDigite o nome: ");
    int escolha = get_int ("\rNúmero: ");
    fprintf(file, "%s , %i\n", nome, escolha);
    fclose (file);

}