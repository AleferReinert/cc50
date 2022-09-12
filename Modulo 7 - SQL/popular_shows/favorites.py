import csv

titles = {}

with open("favorites.csv") as file:
    reader = csv.DictReader(file)

    for row in reader:
        title = row["title"].strip().lower()

        # Se o titulo ainda não existir, inicializa em 0, caso contrário incrementa
        if title not in titles:
            titles[title] = 0
        titles[title] += 1

# Classifica a lista pelos titulos mais populares
for title in sorted(titles, key=lambda title: titles[title], reverse=True):
     print(title, titles[title])