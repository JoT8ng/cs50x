from cs50 import get_float


def main():
    # Ask how many cents the customer is owed
    while True:
        cents = get_float('Changed Owed: ')
        if cents > 0:
            break

    # Prevent floating point imprecision
    cents = round(cents * 100)

    # Calculate the number of quarters to give the customer
    quarters = calculate_quarters(cents)
    cents -= quarters * 25

    # Calculate the number of dimes to give the customer
    dimes = calculate_dimes(cents)
    cents -= dimes * 10

    # Calculate the number of nickels to give the customer
    nickels = calculate_nickels(cents)
    cents -= nickels * 5

    # Calculate the number of pennies to give the customer
    pennies = calculate_pennies(cents)
    cents -= pennies * 1

    # Sum coins
    coins = quarters + dimes + nickels + pennies

    # Print total number of coints to give the customer
    print(coins)


def calculate_quarters(cents):
    q = 0
    while cents >= 25:
        cents -= 25
        q += 1
    return q


def calculate_dimes(cents):
    d = 0
    while cents >= 10:
        cents -= 10
        d += 1
    return d


def calculate_nickels(cents):
    n = 0
    while cents >= 5:
        cents -= 5
        n += 1
    return n


def calculate_pennies(cents):
    p = 0
    while cents >= 1:
        cents -= 1
        p += 1
    return p


main()