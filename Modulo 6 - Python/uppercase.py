from cs50 import get_string

text = get_string("Before: ")
text_formated = text.upper()

# for c in text:
#     print(c.upper(), end="")
# print()
print(f"After: {text_formated}")
