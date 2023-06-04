from cs50 import get_int


# Prompot user input for a card number
while True:
    number = get_int('Number: ')
    if number > 0:
        break

# Check if input card number is a card number
card = number
digits = 0
while card != 0:
    card = card // 10
    digits += 1

# Get sum of every other digit multiplied by 2
i = number
firstsum = 0
modulo = 0
timestwo = 0
while i > 0:
    modulo = i % 100 // 10
    timestwo = modulo * 2
    if timestwo >= 10:
        firstsum = firstsum + (timestwo % 10) + (timestwo // 10)
    elif timestwo < 10:
        firstsum = firstsum + timestwo
    i = i // 100

# Get sum of digits not multiplied by 2
j = number
secondsum = 0
twomodulo = 0
while j > 0:
    twomodulo = j % 100
    twomodulo = twomodulo % 10
    secondsum += twomodulo
    j = j // 100

# Add sum to sum of digits not multiplied by 2
checksum = firstsum + secondsum

# Check if total modulo 10 is congruent to 0 and card type
k = 0
decimals = 10
for k in range(digits - 2):
    decimals = decimals * 10
firstdigit = number // decimals
seconddigit = number // (decimals // 10)

if checksum % 10 == 0:
    if (seconddigit == 34 or seconddigit == 37) and digits == 15:
        print('AMEX')
    elif (50 < seconddigit and seconddigit < 56) and digits == 16:
        print('MASTERCARD')
    elif firstdigit == 4 and (digits == 13 or digits == 16):
        print('VISA')
    else:
        print('INVALID')
else:
    print('INVALID')