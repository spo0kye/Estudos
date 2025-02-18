import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        # TODO: Add the user's entry into the database
        name = request.form.get("name")
        month = int(request.form.get("month"))
        day = int(request.form.get("day"))
        meses30 = [4, 6, 9, 11]
        if (month == 2 and day > 29) or (month in meses30 and day > 30) or (day > 31 or day < 1):
            return render_template("error.html", msg="Invalid Name or Date")
        else:
            db.execute("INSERT INTO birthdays(name, month, day) VALUES (?, ?, ?)", name, month, day)
            return redirect("/")

    else:
        # TODO: Display the entries in the database on index.html
        data = db.execute("SELECT * FROM birthdays ORDER BY month ASC, day ASC")
        return render_template("index.html", db=data)


app.run()