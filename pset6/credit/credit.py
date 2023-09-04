from cs50 import get_int

# Prompt user for a card number. Must be an integer with no hyphen or symbol.
card = get_int("Enter a card number\n")
print(f"Number: {card}")

# Calculate checksum:
# Multiply every other digit by 2, starting with the second-to-last digit ans add them together
tempcard = card
tempcard = int(tempcard / 10)
digit = (tempcard % 10) * 2
counter = 0

# If the product is > 9, then add the products' digit together
if (digit > 9):
    digit = int(digit % 10) + int(digit / 10)

total = digit

while (tempcard >= 1):
    tempcard = int(tempcard / 100)
    digit = (tempcard % 10) * 2

    # If the product is > 9, then add the products' digit together
    if (digit > 9):
        digit = int(digit % 10) + int(digit / 10)

    total += digit
    counter += 1

# Add the sum to the sum of digits that were not multiplied by 2
tempcard = card

while (tempcard >= 1):
    digit = int(tempcard % 10)
    tempcard = int(tempcard / 100)
    total += digit
    counter += 1

# If the total's last digit is 0, it passes that first step
if (total % 10 == 0):
    # Check for card length and starting digits and print card name or if it is an invalid number

    # Check conditions for AMEX
    first = int(card / 10**(counter - 2))
    if (counter == 15 and (first == 34 or first == 37)):
        print("AMEX")

    # Check conditions for Mastercard
    elif (counter == 16 and (first >= 51 and first <= 55)):
        print("MASTERCARD")

    # Check conditions for VISA
    elif ((counter == 13 or counter == 16) and int(first / 10) == 4):
        print("VISA")

    else:
        print("INVALID")

else:
    print("INVALID")