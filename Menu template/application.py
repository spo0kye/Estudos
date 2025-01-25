from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, jsonify
from flask_session import Session
from flask_limiter import Limiter
from flask_limiter.util import get_remote_address
from tempfile import mkdtemp
from functools import wraps
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash


# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True
limiter = Limiter(get_remote_address, app=app)

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["X-UA-Compatible"] = "IE=Edge,chrome=1"
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    response.headers['Cache-Control'] = 'public, max-age=0'
    return response


def login_required(f):
    """
    Decorate routes to require login.

    https://flask.palletsprojects.com/en/1.1.x/patterns/viewdecorators/
    """
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") != 5:
            return redirect("/login")
        return f(*args, **kwargs)
    return decorated_function

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///cardapio.db")


@app.route("/")
def index():
    combos = db.execute("SELECT * FROM combos")
    bebidas = db.execute("SELECT * FROM bebidas")
    drinks = db.execute("SELECT * FROM drinks")
    lanches = db.execute("SELECT * FROM lanches")
    portions = db.execute("SELECT * FROM portions")
    return render_template("index.html", combos=combos, bebidas=bebidas, drinks=drinks, lanches=lanches, portions=portions)


@app.route("/login", methods=["GET", "POST"])
@limiter.limit("5/hour", methods=["POST"])
def login():
    
    session.clear()
    
    if request.method == "GET":
        return render_template("login.html")    
    
    pwrd = db.execute("SELECT hash FROM admin WHERE username='" + request.form.get("username") + "'")[0]["hash"]
    if check_password_hash(pwrd, request.form.get("password")):
        session["user_id"] = 5
        return redirect("/adm")
    
    return render_template("login.html", error="Login inválido")
        
        
@app.route("/adm", methods=["GET", "POST"])
@login_required
def adm():
    if request.method == "GET":
        combos=db.execute("SELECT * FROM combos")
        portions=db.execute("SELECT * FROM portions")
        lanches=db.execute("SELECT * FROM lanches")
        bebidas=db.execute("SELECT * FROM bebidas")
        drinks=db.execute("SELECT * FROM drinks")
        return render_template("adm.html", combos=combos, bebidas=bebidas, drinks=drinks, lanches=lanches, portions=portions)
    
    attdb("combos")
    attdb("portions")
    attdb("lanches")
    attdb("bebidas")
    attdb("drinks")
    attdb("diversos")
    return redirect("/adm")


@app.route("/registrar", methods=["GET", "POST"])
def registrar():
    session.clear()
    
    if request.method == "GET":
        return render_template("register.html")
    
    else:
        db.execute("INSERT INTO admin(hash, username) VALUES('" + str(generate_password_hash(request.form.get("password"))) + "', '" + str(request.form.get("username")) + "')")
        return redirect("/")
    
    
@app.route("/novo", methods=["POST"])
@login_required
def novo():
    table = request.form.get("table")
    name = request.form.get("name")
    ingredients = request.form.get("ingredients")
    price = request.form.get("price")
    if len(name) > 1 and len(price) >= 1:
        db.execute("INSERT INTO " + table + "(name, ingredients, price) VALUES ('" + str(name) + "', '" + str(ingredients) + "', "+ str(price) + ")")
    return redirect("/adm")


def attdb(table):
    for i in db.execute("SELECT * FROM " + table):
        nome = request.form.get(i["name"])
        ingredients = request.form.get(str(i["name"] + "ingredients"))
        price = request.form.get(str(i["name"]) + "price")
        if len(nome) <= 1 or len(price) < 1:
            db.execute("DELETE FROM " + table + " WHERE name='" + str(i["name"]) + "'")
        else:
            db.execute("UPDATE " + table + " SET name='" + str(nome) + "' WHERE name='" + str(i["name"]) + "'")
            db.execute("UPDATE " + table + " SET ingredients='" + str(ingredients) + "' WHERE ingredients='" + str(i["ingredients"]) + "'")
            db.execute("UPDATE " + table + " SET price=" + str(price) + " WHERE price=" + str(i["price"]))


if __name__=='__main__':
    app.run(port=5000)