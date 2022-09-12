# Pesquisa um titulo (fornecido pelo usuario) e retorna sua popularidade
import csv
from cs50 import SQL

# Cria um arquivo vazio
open("shows.db", "w").close()

# Abre o arquivo
db = SQL("sqlite:///shows.db")

# Cria as tabelas
db.execute("CREATE TABLE shows (id INTEGER, title TEXT, PRIMARY KEY(id))")
db.execute("CREATE TABLE genres (show_id INTEGER, genre TEXT, FOREIGN KEY(show_id) REFERENCES shows(id))")

with open("favorites.csv") as file:
    reader = csv.DictReader(file)

    for row in reader:

        # Insere os títulos na tabela "shows"
        title = row["title"].strip().upper()
        id = db.execute("INSERT INTO shows (title) VALUES(?)", title)

        # Insere os gêneros na tabela "genres"
        for genre in row["genres"].split(", "):
            db.execute("INSERT INTO genres (show_id, genre) VALUES(?, ?)", id, genre)