# Retorna a quantidade mínima de moedas necessárias para dar o troco
from cs50 import get_float

while True:
    money = get_float("Change owed: ")
    if money > 0:
        break

coin = 0

# Moedas de 25 centavos
while money >= 0.25:
    coin += 1
    money = round(money - 0.25, 2)

# Moedas de 10 centavos
while money >= 0.10:
    coin += 1
    money = round(money - 0.10, 2)

# Moedas de 5 centavos
while money >= 0.05:
    coin += 1
    money = round(money - 0.05, 2)

# Moedas de 1 centavo
while money >= 0.01:
    coin += 1
    money = round(money - 0.01, 2)

print(coin);