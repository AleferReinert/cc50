import cs50

x = cs50.get_int("x: ")
y = cs50.get_int("y: ")

if x > y:
    print("x é maior que y")
elif x < y:
    print("x é menor que y")
else:
    print("x é igual a y")