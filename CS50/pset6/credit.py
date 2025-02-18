from cs50 import get_string
from sys import exit

#Resultado dos primeiros números multiplicado por 2
mult2 = 0

credit = get_string("Digite o número do cartão: ")

#Pula de 2 em 2 à partir do primeir dígito
for i in range(0, len(credit), 2):

    #Verifica a ortografia e retorna um erro caso não seja um número
    if int(credit[i]) > 9:
        print("Erro, número inválido")
        exit(1)

    #Verifica se o número contém 2 casas, caso sim, recebe apenas a unidade, e soma com a dezena
    if (int(credit[i]) * 2) > 9:
        mult2 += (int(credit[i]) * 2) % 10
        mult2 += int((int(credit[i]) / 10 + 0.5))
    else:
        mult2 += (int(credit[i]) * 2)


#soma = Soma de todos os números restantes com o resultado anterior
soma = mult2
for j in range(1, len(credit), 2):
    soma += int(credit[j])

soma += int(credit)

#Verifica se o cartão é valido
if soma % 10 != 0:
    print("INVALID")
    exit(2)

if len(credit) == 15:
    print("AMEX")
    exit(0)

elif credit[0] == 4:
    print("VISA")
    exit(0)

elif len(credit) == 16:
    print("MASTERCARD")
    exit(0)
