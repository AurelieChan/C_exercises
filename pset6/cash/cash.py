from cs50 import get_int
from cs50 import get_float
from math import floor

coins = 0
cash = 0

# Prompt user for an amount of change and save it as a float
while (cash <= 0):
    cash = get_float("Enter an amount of change\n")
print(f"Change owed: {cash:0.2f}")

# Store the amount in a cent value
cents = round(cash * 100)

# Divide the amount by the value of each coins to know how many of them to give
# Use the reminder to get the result with smaller coins
if (cents >= 25):
    coins += floor(cents / 25)
    cents %= 25

if (cents >= 10):
    coins += floor(cents / 10)
    cents %= 10

if (cents >= 5):
    coins += floor(cents / 5)
    cents %= 5

coins += cents

# Print the number of coins to be given
print(f"{coins}")