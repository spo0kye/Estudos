#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    char *text = get_string("\rDigite o texto: ");
    int letters = 0;
    int sentences = 0;
    int palavras = 1;
    for (int count = 0; count < strlen(text); count++)
    {
        if(text[count] >= 65 && text[count] <= 90)
            letters++;

        else if((text[count]) >= 97 && text[count] <= 122)
            letters++;

        else if((text[count]) == 32)
            palavras++;

        else if((text[count]) == 33 || text[count] == 46 || text[count] == 63)
            sentences++;
    }
    double index = ((0.0588 * ((float)letters / palavras * 100.0)) - (0.296 * ((float)sentences / palavras * 100.0)) - 15.8 + 0.4);
    if (index < 1)
     printf("\rBefore grade 1 %d\n", (int)index);

    else
     printf("\rGrade %d\n", (int)index);

    return 0;
}