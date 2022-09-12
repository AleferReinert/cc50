# Pesquisa um titulo (fornecido pelo usuario) e retorna sua popularidade
import csv

title = input("Title: ")

with open("favorites.csv") as file:
    reader = csv.DictReader(file)

    counter = 0
    for row in reader:
        if row["title"].strip().lower() == title.strip().lower():
            counter +=1

print(f"{title}: {counter}")