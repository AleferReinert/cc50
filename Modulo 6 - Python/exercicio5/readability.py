from cs50 import get_string

text = get_string("Text: ")
letters = 0;
words = 1;
phrases = 0;

for i in text:

    # Calcula a quantidade de letras
    if i.isalpha() or i.isnumeric():
        letters +=1

    # Calcula a quantidade de palavras
    elif i == ' ':
        words +=1

    # Calcula a quantidade de frases
    elif i == '.' or i == '!' or i == '?':
        phrases += 1

average_letters_by_words = (letters / words) * 100
average_phrases_by_words = (phrases / words) * 100

result = round((0.0588 * average_letters_by_words) - (0.296 * average_phrases_by_words)  - 15.8)

if result >= 16:
    print("Grade 16+")
elif result < 1:
    print("Before Grade 1")
else:
    print(f"Grade {result}")