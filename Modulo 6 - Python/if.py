answer = input("Qual seu nome?\n")
age = int(input("Qual sua idade?\n"))

if age < 12:
    print(f"{answer}, você é uma criança de {age} anos.")
elif age >= 12 and age < 18:
    print(f"{answer}, você é um adolescente de {age} anos.")
else:
    print(f"{answer}, você é um adulto de {age} anos.")