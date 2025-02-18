import csv

from cs50 import get_string

with open("phonebook.csv", "a") as file:
    name = get_string("Nome: ")
    number = get_string("Numero: ")
    writer = csv.writer(file)
    writer.writerow((name, number))
