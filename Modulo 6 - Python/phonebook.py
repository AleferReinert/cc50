# Procura o nome de uma pessoa la lista telefônica e retorna o número de telefone
from cs50 import get_string

people = {
    "Aulas de bateria": "47 99955-8118",
    "Alefer": "47 99933-5501",
    "Brian": "48 9821-3451"
}

name = get_string("Name: ")

if name in people:
    print(f"{people[name]}")