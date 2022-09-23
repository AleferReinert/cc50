import os
from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret'

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        name = request.form.get('name')
        month = request.form.get('month')
        day = request.form.get('day')
        month = int(month)
        day = int(day)

        # Validação de name
        if not name or name.isalpha() == False:
            flash('Invalid name.', 'error')
            return redirect("/")

        # Validação de month
        if not month or month < 1 or month > 12:
            flash('Invalid month.', 'error')
            return redirect("/")

        # Validação de day
        if not day or day < 1 or day > 31:
            flash('Invalid day.', 'error')
            return redirect("/")

        db.execute('INSERT INTO birthdays (name, month, day) VALUES(?, ?, ?)', name, month, day)
        flash(f'{name} birthday added!', 'success')
        return redirect("/")

    else:
        data = db.execute('SELECT name, month, day FROM birthdays ORDER BY name')
        return render_template("index.html", birthdays=data)