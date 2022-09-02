# Verifica se um cartão de crédito é valido e retorna a bandeira
from cs50 import get_string

number = get_string("Number: ")

# Dois primeiros digitos
digits = number[0] + number[1]

if digits == "34" or digits == "37":
    print("AMEX")

elif digits >= "51" and digits <= "55":
    print("MASTERCARD")

elif digits >= "40" and digits <= "49":
    print("VISA")

else:
    print("INVALID")
