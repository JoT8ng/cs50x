import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user = session["user_id"]

    # Query user stocks
    stocks = db.execute(
        "SELECT symbol, SUM(shares) AS shares FROM transactions GROUP BY symbol HAVING user_id = ? AND SUM(shares) > 0", user)

    # Calculate user's sum and balance
    row = db.execute("SELECT cash FROM users WHERE id = ?", user)
    balance = row[0]["cash"]
    sum = balance

    # Index if user bought no stocks
    if len(stocks) == 0:
        return render_template("index.html", balance=balance, sum=sum)

    # Lookup all stocks user bought
    for stock in stocks:
        # Calculate the current price of stock
        quote = lookup(stock["symbol"])
        stock["name"] = quote["name"]
        price = quote["price"]
        total = price * int(stock["shares"])

        # Enter into database/dict
        stock["total"] = total
        stock["price"] = price

        sum += total

    return render_template("index.html", stocks=stocks, balance=balance, sum=sum)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")

        # Ensure user submitted stock symbol
        if not request.form.get("symbol"):
            return apology("must provide valid symbol", 400)

        # Lookup stock symbol unsuccessful
        elif not lookup(symbol):
            return apology("Unable to look up stock, stock symbol does not exist", 400)

        # Ensure user submitted number of shares
        elif not request.form.get("shares"):
            return apology("must provide number of shares", 400)

        # Ensure user submits shares as a positive number
        elif shares.isnumeric() == False:
            return apology("Share number must be a postive integer")

        # Ensure user submits shares as not float
        elif isinstance(shares, float) or float(shares) < 0:
            return apology("Share number must be a postive integer")

        shares = int(shares)

        # Look up stock price
        if lookup(symbol):
            quote = lookup(symbol)
            cost = shares * quote["price"]

            # Ensure user has enough money to buy stock
            user = session["user_id"]
            row = db.execute("SELECT cash FROM users WHERE id = ?", user)
            if row[0]["cash"] < cost:
                return apology("not enough cash", 400)

            # Buy stock(s)
            else:
                # Calculate user balance
                balance = row[0]["cash"] - cost

                # Update database
                db.execute("UPDATE users SET cash=? WHERE id=?", balance, user)
                db.execute("INSERT INTO transactions (symbol, shares, price, timestamp, user_id) VALUES (?, ?, ?, CURRENT_TIMESTAMP, ?)",
                           symbol, shares, quote["price"], user)

                return redirect("/")

        # Ensure user submits shares > 0
        elif shares < 1:
            return apology("must provide number of shares", 400)

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user = session["user_id"]

    # Query user stocks
    stocks = db.execute(
        "SELECT * FROM transactions WHERE user_id = ?", user)

    for stock in stocks:
        quote = lookup(stock["symbol"])
        stock["name"] = quote["name"]

    return render_template("history.html", stocks=stocks)


@app.route("/addcash", methods=["GET", "POST"])
@login_required
def addcash():
    """Allow user to add additional cash"""
    user = session["user_id"]

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure user submitted cash
        if not request.form.get("cash"):
            return apology("please provide cash amount", 400)

        # Buy stock(s)
        else:
            # Calculate user balance
            row = db.execute("SELECT cash FROM users WHERE id = ?", user)
            newcash = request.form.get("cash")
            balance = int(row[0]["cash"]) + int(newcash)

            # Update database with new user cash amount
            db.execute("UPDATE users SET cash=? WHERE id=?", balance, user)

            return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("addcash.html")


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
    """Get stock quote."""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        symbol = request.form.get("symbol")

        # Ensure user insert stock symbol
        if not request.form.get("symbol"):
            return apology("must provide valid symbol", 400)

        # Lookup stock symbol unsuccessful
        elif not lookup(symbol):
            return apology("Unable to look up stock, stock symbol does not exist", 400)

        # Lookup stock symbol successful
        quote = lookup(symbol)
        return render_template("quoted.html", quote=quote)

    # User reached route via GET
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure password confirmation was submitted
        elif not request.form.get("confirmation"):
            return apology("must provide password confirmation", 400)

        # Ensure username is not already used
        elif len(rows) != 0:
            return apology("username is already taken", 400)

        # Ensure passwords match
        elif not password == confirmation:
            return apology("passwords do not match", 400)

        else:
            # Generate password hash
            hash = generate_password_hash(password, method="pbkdf2:sha256", salt_length=8)

            # Insert user into database
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)

            return redirect("/")

    # User reached route via GET
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user = session["user_id"]

    # Query user stocks
    stocks = db.execute(
        "SELECT symbol, SUM(shares) AS shares FROM transactions GROUP BY symbol HAVING user_id = ? AND SUM(shares) > 0", user)

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")
        owned_shares = db.execute(
            "SELECT SUM(shares) AS shares FROM transactions GROUP BY symbol HAVING user_id = ? AND symbol = ?", user, symbol)
        total_shares = owned_shares[0]["shares"]

        # Ensure user submitted stock symbol
        if not request.form.get("symbol"):
            return apology("must provide valid symbol", 400)

        # Ensure user submitted number of shares
        elif not request.form.get("shares"):
            return apology("must provide number of shares", 400)

        # Ensure user submits shares > 0
        elif int(shares) <= 0:
            return apology("must provide number of shares", 400)

        shares = int(shares)

        for stock in stocks:
            # Ensure user has enough shares to sell
            if shares > total_shares:
                return apology("Not enough shares to sell")

            # Sell stock
            else:
                quote = lookup(symbol)
                sale = shares * quote["price"]
                shares = -abs(shares)

                row = db.execute("SELECT cash FROM users WHERE id = ?", user)
                balance = sale + row[0]["cash"]

                # Update users transactions table/database
                db.execute("UPDATE users SET cash=? WHERE id=?", balance, user)

                # Insert sale into transactions database
                db.execute("INSERT INTO transactions (symbol, shares, price, timestamp, user_id) VALUES(?, ?, ?, CURRENT_TIMESTAMP, ?)",
                           symbol, shares, quote["price"], user)

                return redirect("/")

    # User reached route via GET
    else:
        return render_template("sell.html", stocks=stocks)