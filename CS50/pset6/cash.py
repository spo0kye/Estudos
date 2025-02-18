from cs50 import get_float
from sys import exit

moeda = 0
valor = get_float("Digite um valor: ")
if valor < 0.01:
    print("Erro, valor inválido")
    exit(1)

while valor > 0.009:
    print(f"{valor}")

    if valor >= 0.2499:
        moeda += 1
        valor -= 0.25

    elif valor >= 0.0999:
        moeda += 1
        valor -= 0.10

    elif valor >= 0.0499:
        moeda += 1
        valor -= 0.05

    else:
        moeda += 1
        valor -= 0.01

if moeda == 1:
    print("Será necessário no mínimo 1 moeda")
else:
    print(f"Será necessário no mínimo {moeda} moedas")
exit(0)
