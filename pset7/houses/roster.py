import sys
from cs50 import SQL

if len(sys.argv) <= 1:
    print("Usage: python roster.py house")
    exit(1)

namehouse = sys.argv[1]

# Acces to the DB
db = SQL("sqlite:///students.db")

# Run a query to get the list of students living in the specific house
rows = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first", namehouse)

# Print the list of students
for row in rows:
    if (row["middle"] is None):
        print(row["first"], " ", row["last"], ", born ", row["birth"], sep="")
    else:
        print(row["first"], " ", row["middle"], " ", row["last"], ", born ", row["birth"], sep="")