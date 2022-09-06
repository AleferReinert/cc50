from sys import argv, exit
import csv

def main():
    if len(argv) != 3:
        print("Usage: python dna.py database.csv sequence.csv")

    database_file = argv[1]
    sequence_file = argv[2]
    strs = {}

    # Verifica as STR existentes e adiciona ao dict
    with open(database_file, "r") as file:
        reader = csv.DictReader(file)
        fieldnames = reader.fieldnames[1:]

        for i in fieldnames:
            strs[i] = 0

    # Atualiza o dict com o maior numero de repetições consecutivas de cada STR
    with open(sequence_file, "r") as file:
        s = file.readline()

        for i in strs:
            strs[i] = find_repeats(i, s)

    # Faz as comparações e da um retorno
    with open(database_file, "r") as file:
        reader = csv.DictReader(file)

        # Conta quantos valores são iguais
        found_len = 0
        found = False
        for row in reader:
            for i in strs:
                if int(row[i]) == strs[i]:
                    found_len += 1

                    # Se todos valores forem iguais, é porque foi encontrado
                    if found_len == len(strs):
                        found = True
                        print(row['name'])
                        exit(0)
                else:
                    found_len = 0

        if found == False:
            print("No match")

def find_repeats(str, sequence):
    l = len(str)
    repeat = 2
    max_repeat = 0
    total = 0
    for i in range(len(sequence)):
        prev = sequence.find(str, int(i-l), int(i-l)+l)
        current = sequence.find(str, int(i), int(i)+l)
        next = sequence.find(str, int(i+l), int(i+l)+l)

        if current != -1:
            total+=1

        if total == 1:
            max_repeat = 1
        else:
            if current != -1 and next == (current + l) and prev == (current - l):
                repeat +=1
            if next == -1 and repeat > max_repeat:
                max_repeat = repeat

    return max_repeat

main()