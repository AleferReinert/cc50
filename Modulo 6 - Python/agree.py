from cs50 import get_string

answer = get_string("Do you agree? ")

if answer.lower() in ["y","yes"]:
    print("Agreed.")
elif answer.lower() in ["n", "not"]:
    print("Not agreed.")
else:
    print("Use yes or not.")