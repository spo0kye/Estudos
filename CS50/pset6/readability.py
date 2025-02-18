from cs50 import get_string
from sys import exit
from decimal import *

def main():
    texto = get_string("Digite o texto: ")
    if len(texto) <= 1:
        print("Invalid text")
        exit(1)

    sentences = 0
    letras = 0
    palavras = 1
    for i in range(len(texto)):
        if texto[i] == '!' or texto[i] == '.' or texto[i] == '?':
            sentences += 1

        elif texto[i] == " ":
            palavras += 1

        elif texto[i].upper() >= 'A' and texto[i].upper() <= 'Z':
            letras += 1

    s = Decimal(sentences) / Decimal(palavras) * 100
    l = Decimal(letras) / Decimal(palavras) * 100
    index = (Decimal(0.0588) * l) - (Decimal(0.296) * s) - Decimal(15.8)

    if index <= 1:
        print("Before Grade 1")
        exit(0)

    elif index > 16:
        print("Grade 16+")
        exit(0)

    else:
        print(f"Grade: {round(index)}")
        exit(0)

main()
