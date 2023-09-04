from cs50 import get_string

valchar = 0
space = 0
sent = 0
word = 0

# Prompt user to enter a text
text = get_string("Text: ")

for i in text:
    # Get alphabet letters
    if (i.isalpha() == True):
        valchar += 1

    # Get spaces
    elif (i.isspace() == True):
        space += 1

    # Get punctuations marking end of a sentence
    elif (i == "." or i == "!" or i == "?"):
        sent += 1

word = (space + 1)

# Implementing the formula
L = float(valchar) / (float(word) / 100)
S = float(sent) / (float(word) / 100)
index = 0.0588 * L - 0.296 * S - 15.8

if (round(index) < 1):
    print("Before Grade 1")

elif (round(index) > 16):
    print("Grade 16+")

else:
    print(f"Grade {round(index)}")