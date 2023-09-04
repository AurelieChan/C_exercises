import csv
import sys
from cs50 import SQL

if len(sys.argv) <= 1:
    print("Usage: python import.py characters.csv")
    exit(1)

csvfile = sys.argv[1]

data = []

# Open the CSV file and read contents
with open(csvfile, "r") as characters:
    reader = csv.DictReader(characters)
    for row in reader:
        data.append(row)

# Acces to the DB
db = SQL("sqlite:///students.db")

for row in data:
    # Split the names
    name = row["name"]
    splitname = name.split()

    # If there are 3 names, put the 1st name in column FIRST in the DB, 2nd in MIDDLE and 3rd in LAST
    if (len(splitname) == 3):
        first = splitname[0]
        middle = splitname[1]
        last = splitname[2]

    # If there are 2 names, put the 1st name in column FIRST, none so MIDDLE is NULL and 2nd name in LAST
    elif (len(splitname) == 2):
        first = splitname[0]
        middle = None
        last = splitname[1]

    # Add datas in the SQL database
    db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
               first, middle, last, row["house"], row["birth"])