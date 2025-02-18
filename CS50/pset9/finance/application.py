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


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    row = db.execute("SELECT cash FROM users WHERE id = (?)", session["user_id"])[0][
        "cash"
    ]
    possession = db.execute(
        "SELECT * FROM possession WHERE user_id = (?)", session["user_id"]
    )
    global total
    total = []
    for i in range(len(possession)):
        total.insert(i, usd(possession[i]["value"] * possession[i]["quantity"]))

    for j in range(len(possession)):
        possession[j]["value"] = usd(possession[j]["value"])

    return render_template(
        "index.html", money=usd(row), total=total, possession=possession
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    else:
        stock = request.form.get("stock")
        amount = int(request.form.get("amount"))
        stockprice = lookup(stock)["price"]
        if (
            amount * stockprice
            <= db.execute("SELECT cash FROM users WHERE id=(?)", session["user_id"])[0][
                "cash"
            ]
        ):
            db.execute(
                "INSERT INTO possession(user_id, stock, value, quantity) VALUES (?, ?, ?, ?)",
                session["user_id"],
                stock,
                stockprice,
                amount,
            )
            db.execute(
                "UPDATE users SET cash = cash - ? WHERE id = ?",
                amount * stockprice,
                session["user_id"],
            )
            db.execute(
                "INSERT INTO history(user_id, stock, quantity, value, operation) VALUES (?, ?, ?, ?, ?)",
                session["user_id"],
                stock,
                amount,
                stockprice,
                "buy",
            )
            return redirect("/history")
        else:
            return apology("Error", "/buy")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return render_template(
        "history.html",
        history=db.execute(
            "SELECT * FROM history WHERE user_id = (?)", session["user_id"]
        ),
    )


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", "/login", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", "/login", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", "/login", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        session["name"] = rows[0]["username"]

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
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html", dict=0)
    else:
        return render_template("quote.html", dict=lookup(request.form.get("stock")))


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        if not request.form.get("username"):
            return apology("Required username", "/register", 403)
        elif not request.form.get("password"):
            return apology("Required password", "/register", 403)

        if not db.execute(
            "SELECT username FROM users WHERE username = (?)",
            request.form.get("username"),
        ):
            db.execute(
                "INSERT INTO users(username, hash) VALUES (?, ?);",
                request.form.get("username"),
                generate_password_hash(request.form.get("password")),
            )
            session["user_id"] = db.execute(
                "SELECT id FROM users WHERE username = (?)",
                request.form.get("username"),
            )[0]["id"]
            session["name"] = request.form.get("username")
            return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        return render_template("sell.html")
    else:
        stock = request.form.get("stock")
        amount = int(request.form.get("amount"))
        stockprice = lookup(stock)["price"]
        if (
            amount
            <= db.execute(
                "SELECT quantity FROM possession WHERE user_id=(?)", session["user_id"]
            )[0]["quantity"]
        ):
            db.execute(
                "DELETE FROM possession WHERE stock = ? AND user_id = ?",
                stock,
                session["user_id"],
            )
            db.execute(
                "UPDATE users SET cash = cash + ? WHERE id = ?",
                amount * stockprice,
                session["user_id"],
            )
            db.execute(
                "INSERT INTO history(user_id, stock, quantity, value, operation) VALUES (?, ?, ?, ?, ?)",
                session["user_id"],
                stock,
                amount,
                stockprice,
                "sell",
            )

            return redirect("/history")
        else:
            return apology("Error", "/buy")


@app.route("/look", methods=["POST"])
@login_required
def look():
    """real time sum of stocks"""
    soma = 0
    for row in db.execute(
        "SELECT * FROM possession WHERE user_id = (?)", session["user_id"]
    ):
        soma += lookup(row["stock"])["price"] * row["quantity"]
    return str(usd(soma))


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
