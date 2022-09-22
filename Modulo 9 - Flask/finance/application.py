import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    purchases = []
    total = 0
    rows = db.execute("SELECT * FROM purchases WHERE user_id=?", session["user_id"])
    for row in rows:
        total += (row['shares'] * row['price'])
        data = lookup(row['symbol'])
        row['name'] = data['name']
        row['total'] = usd(row['shares'] * row['price'])
        row['price'] = usd(row['price'])
        purchases.append(row)
    return render_template("index.html", purchases=purchases, total=usd(total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "GET":
        return render_template("buy.html")

    if request.method == "POST":
        # Obriga a inserir um symbol valido
        symbol = request.form.get("symbol")
        data = lookup(symbol)
        if not symbol:
            return apology("Missing symbol")
        if data == None:
            return apology("Symbol not found")

        # Obriga a inserir um número válido em shares
        shares = request.form.get("shares")
        if not shares:
            return apology("Missing shares")
        if shares <= '0':
            return apology("Shares request a positive number")

        data = lookup(symbol)
        current_cash = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])

        if current_cash[0]['cash'] < data["price"]:
            return apology("Insufficient funds")

        db.execute("CREATE TABLE IF NOT EXISTS purchases (id INTEGER, user_id INTEGER NOT NULL, symbol TEXT NOT NULL, price NUMERIC NOT NULL, shares INTEGER NOT NULL, PRIMARY KEY(id), FOREIGN KEY(user_id) REFERENCES users(id))")
        db.execute("INSERT INTO purchases (user_id, symbol, price, shares) VALUES(?, ?, ?, ?)", session["user_id"], data["symbol"], data["price"], shares)
        return redirect("/")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "GET":
        return render_template("quote.html")
    if request.method == "POST":
        data = lookup(request.form.get("symbol"))
        return render_template("quoted.html", symbol=data["symbol"], company=data["name"], price=usd(data["price"]))


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "GET":
        return render_template("register.html")

    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Se campo username estiver em branco
        if not username:
            return apology("Missing username")

        # Verifica se o username já existe
        if username:
            user_exist = db.execute("SELECT username FROM users WHERE username = ?", username)
            if  len(user_exist) > 0:
                return apology("Username already exist")

        # Se os dois campos de senha não estiverem preenchidos
        if not password or not confirmation:
            return apology("Missing password")

        # Se as senhas não forem iguais
        if password != confirmation:
            return apology("Passwords do not match")

        # Insere o usuário no banco de dados
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, generate_password_hash(password))
        return redirect("/login")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
