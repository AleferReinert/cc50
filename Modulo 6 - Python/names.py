# Coloca os nomes em minusculo para fazer uma busca correta,
# onde encontrará o nome independente da formatação

from cs50 import get_string

names = ["Bill", "Charlie", "Fred", "George", "Ginny", "Percy", "Ron"]
names_f = []

for name in names:
    name_f = name.lower()
    names_f.append(name_f)

s = get_string("Name: ")

if s.lower() in names_f:
    print(f"{s} found.")
else:
    print("Not found.")