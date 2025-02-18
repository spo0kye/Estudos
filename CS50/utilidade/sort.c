int
main(void)
{
    float vl[nprodutos];
    float menor = 0;
    float maior = 0;
    for (int contador = 0; contador < nprodutos; contador++)
    {
        vl[contador] = get_float ("\rDigite o valor do produto: ");
        if (contador == 0)
        {
            menor = vl[contador];
            maior = vl[contador];
        }
        else if (contador != 0)
        {
            if (vl[contador] < menor)
                menor = vl[contador];
            else if (vl[contador] > maior)
                maior = vl[contador];
        }
    }
}