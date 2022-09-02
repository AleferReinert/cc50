# Adiciona contatos a uma lista telefonica

from cs50 import get_string
import csv

# Dessa forma não há necessidade de fechar o arquivo, isso acontece automaticamente
with open("phonebook.csv", "a") as file: # Anexar
    name = get_string("Name: ")
    number = get_string("Number: ")

    # csv.writer() espera por um arquivo já aberto
    writer = csv.writer(file)
    writer.writerow([name, number])