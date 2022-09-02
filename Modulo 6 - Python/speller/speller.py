words = set()

# verifica se existe cada palavra no dicionário
def check(word):
    if word.lower() in words:
        return True
    else:
        return False

# Carrega o dicionário
def load(dictionary):
    file = open(dictionary, "r")
    for line in file:
        words.add(line.rstrip) # rstrip remove os espaços em branco, como barra de espaço, tabs e \n
    file.close()
    return True

# retorna o número de palavras existentes no conjunto de palavras
def size():
    return len(words)

# descarregar memória
def unload():
    return True
