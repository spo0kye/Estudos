import pandas as pd
import sys
import time
#from msvcrt import getch

file1 = "arquivo1.xlsx"
file2 = "arquivo2.xlsx"
file3 = "arquivo3.xlsx"

colunas = []
quantidade_colunas = int(input("Digite a quantidade de colunas: "))
for _ in range(quantidade_colunas):
    colunas.append(input("Digite o nome exato da coluna desejada: "))


def verificar(tabelas: list[int(quantidade_colunas)]): # type: ignore
    lista = []
    for coluna in colunas:
        divergência1_2 = tabelas[0][coluna] != tabelas[1][coluna]
        divergência1_3 = tabelas[0][coluna] != tabelas[2][coluna]
        divergência2_3 = tabelas[1][coluna] != tabelas[2][coluna]

        lista.append(tabelas[0][coluna][divergência1_2]) if not divergência1_2.empty else None
        breakpoint()
        lista.append(tabelas[0][coluna][divergência1_3]) if not divergência1_3.empty else None
        lista.append(tabelas[2][coluna][divergência2_3]) if not divergência2_3.empty else None

    return lista

def files():
    tabela1 = pd.read_excel(file1)
    tabela2 = pd.read_excel(file2)
    tabela3 = pd.read_excel(file3)
    return verificar([tabela1, tabela2, tabela3])


def main():
    print(files())

main()