#include <stdio.h>
#include <stdlib.h>



int main(void)
{
    // Faz com que tenha certeza de que o valor foi ajustado para um múltiplo do tamanho desejado, pois acessar...
    // um valor que esteja quebrado em 2 partes da memória pode causar crash em algumas arquiteturas ou comportamento inesperado

    // FUNCIONAMENTO: memória apontada para (exemplo) 22, soma o tamanho do tipo desejado - 1 (ex. 7) e depois subtrai de forma binária...
    // para queseja divisivel inteiramente pelo mesmo (ex. 28 não é exato, logo seria 24)

    void *raw = malloc(64);
    uintptr_t aligned =
    (uintptr_t)((uintptr_t)raw + 2 + _Alignof(double) - 1) & ~(_Alignof(double) - 1);
    double *d = (double *)aligned;
   
}