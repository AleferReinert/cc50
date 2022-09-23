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

# Create table of transactions
db.execute("CREATE TABLE IF NOT EXISTS transactions (id INTEGER, user_id INTEGER NOT NULL, symbol TEXT NOT NULL, shares INTEGER NOT NULL DEFAULT 0, price NUMERIC NOT NULL, timestamp NUMERIC, PRIMARY KEY(id), FOREIGN KEY(user_id) REFERENCES users(id))")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    # Saldo total em ações
    shares_total = 0

    # Saldo em dinheiro
    cash = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])

    # Listagem das ações compradas
    purchases = []
    rows = db.execute("SELECT symbol, shares FROM transactions WHERE user_id=? AND shares > 0", session["user_id"])
    for row in rows:
        data = lookup(row['symbol'])
        row['name'] = data['name']
        row['price'] = usd(data['price'])
        row['total'] = usd(row['shares'] * data['price'])
        shares_total += (row['shares'] * data['price'])
        purchases.append(row)
    return render_template("index.html", purchases=purchases, cash=usd(cash[0]['cash']),total=usd(cash[0]['cash'] + shares_total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "GET":
        return render_template("buy.html")

    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        timestamp = request.form.get("timestamp")
        data = lookup(symbol)

        # Validação de symbol
        if not symbol:
            return apology("Missing symbol")
        if data == None:
            return apology("Symbol not found")

        # Validação de shares
        if not shares:
            return apology("Missing shares")
        if shares.isnumeric() == False:
            return apology("Shares request a integer")
        if int(shares) <= 0:
            return apology("Shares request a positive number")

        # Dinheiro atual do usuário
        current_cash = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])

        # Dinheiro total da ação a ser comprada
        total_buy = (float(shares) * data["price"])

        # Verifica se tem saldo suficiente para a compra
        if current_cash[0]['cash'] < total_buy:
            return apology("Insufficient funds")

        # Efetua a compra
        update_cash = (current_cash[0]['cash'] - total_buy)
        db.execute("UPDATE users SET cash=? WHERE id=?", update_cash, session["user_id"])
        db.execute("INSERT INTO transactions (user_id, symbol, price, shares, timestamp) VALUES(?, ?, ?, ?, ?)", session["user_id"], data["symbol"], data["price"], shares, timestamp)
        flash('Bought!','success')
        return redirect('/')

@app.route("/history")
@login_required
def history():
    transactions = db.execute("SELECT symbol, shares, price, timestamp FROM transactions WHERE user_id=?", session['user_id'])
    return render_template("history.html", transactions=transactions)


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
        symbol = request.form.get("symbol")
        data = lookup(symbol)

        # Validação de symbol
        if not symbol:
            return apology('Missing symbol')
        if data == None:
            return apology('Invalid symbol')
        return render_template("quoted.html", symbol=data["symbol"], company=data["name"], price=usd(data["price"]))


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "GET":
        return render_template("register.html")

    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Validação de username
        if not username:
            return apology("Missing username")
        if username:
            user_exist = db.execute("SELECT username FROM users WHERE username = ?", username)
            if  len(user_exist) > 0:
                return apology("Username already exist")

        # Validação de senha
        if not password or not confirmation:
            return apology("Missing password")
        if password != confirmation:
            return apology("Passwords do not match")

        # Registra o usuário
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, generate_password_hash(password))
        flash('Registered!','success')
        return redirect("/login")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    # Lista de symbols válidos
    symbols = []
    rows = db.execute("SELECT DISTINCT(symbol) FROM transactions WHERE user_id=?", session["user_id"])
    for row in rows:
        symbols.append(row['symbol'])

    if request.method == "GET":
        return render_template("sell.html", symbols=symbols)

    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        timestamp = request.form.get("timestamp")
        data = lookup(symbol)

        # Validação de symbol
        if not symbol:
            return apology("Missing symbol")
        if not symbol in symbols:
            return apology("Invalid symbol")

        # Validação de shares
        if not shares:
            return apology("Missing shares")
        if shares <= '0':
            return apology("Shares request a positive number")

        # Verifica se o usuário tem a quantidade de ações que está tentando vender
        shares_sum = db.execute("SELECT SUM(shares) FROM transactions WHERE user_id=? AND symbol=?", session["user_id"], symbol)
        if int(shares) > shares_sum[0]['SUM(shares)']:
            return apology("Unavailable quantity")

        # Efetua a venda
        current_cash = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])
        total_sell = (float(shares) * data['price'])
        db.execute("UPDATE users SET cash=? WHERE id=?", (current_cash[0]['cash'] + total_sell), session["user_id"])
        db.execute("INSERT INTO transactions (user_id, symbol, price, shares, timestamp) VALUES(?, ?, ?, ?, ?)", session["user_id"], data["symbol"], data["price"], (int(shares) * -1), timestamp)
        flash('Sold!','success')
        return redirect("/")

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)