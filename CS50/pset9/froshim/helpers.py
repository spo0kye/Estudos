from cs50 import SQL
from flask import Flask, render_template, request, redirect


db = SQL("sqlite:///froshim.db")

SPORTS = [
    "volei",
    "basquete",
    "futebol"
]

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html", sports=SPORTS)

@app.route("/register", methods=["POST"])
def register():
    nome = request.form.get("name")
    esporte = request.form.get("sport")
    if not nome:
        return render_template("error.html", errmsg = "null name", sports=SPORTS)

    elif not esporte:
        return render_template("error.html", errmsg = "invalid sport", sports=SPORTS)

    else:
        db.execute("INSERT INTO registrants (name, sport) VALUES(?, ?)", nome, esporte)
        return redirect("/registros")



@app.route("/registros")
def registro():
    registrants = db.execute("SELECT * FROM registrants")
    return render_template("registros.html", registros=registrants)