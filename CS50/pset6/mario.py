from cs50 import get_int
from sys import exit

H = get_int("Digite a altura: ")
if H < 1 or H > 8:
    print("Erro, numero inválido")
    exit(1)

for i in range(1, H + 1):
    print(" " * (H - i), end="")
    print("#" * i, end="")
    print("  ", end="")
    print("#" * i)
exit(0)
