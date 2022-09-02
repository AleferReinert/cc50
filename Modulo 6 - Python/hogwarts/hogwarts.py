import csv

houses = {
    "Gryffindor": 0,
    "Hufflepuff": 0,
    "Ravenclaw": 0,
    "Slytherin": 0
}

with open("responses.csv", "r") as file:
    reader = csv.reader(file)
    next(reader) #Pula a primeira linha (timestamp e houses)

    for row in reader:
        house = row[1] # Cada linha é uma lista, está pegando o segundo valor
        houses[house] +=1

for house in houses:
    print(f"{house}: {houses[house]}")