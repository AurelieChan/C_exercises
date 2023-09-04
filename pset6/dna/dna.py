import csv
import sys
import re

if len(sys.argv) <= 2:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)

csvfilename = sys.argv[1]
txtfilename = sys.argv[2]

data = []

# Open the CSV file, read contents into memory
with open(csvfilename, newline='') as database:
    reader = csv.DictReader(database)
    for row in reader:
        data.append(row)

# Get the keys for STR names, by storing the first row of data
keys = [*data[0]]
# Remove 'name' from that array
keys.pop(0)

# Open the DNA sequences files
with open(txtfilename, "r") as dnafile:
    dna = dnafile.read()

# Initialize final count for each DNA pattern
final_count = [0] * len(keys)

for keynumber, eachkey in enumerate(keys):

    dnaiter = re.finditer(rf"{eachkey}", dna)
    sequence = []

    # Construct the list of matched objets
    for match in dnaiter:
        sequence.append(match)

    # For each STR, compute the longest run of consecutive repeats in the DNA sequence
    temp_count = 0

    temp_count += 1
    final_count[keynumber] = max(temp_count, final_count[keynumber])

    for i, pattern in enumerate(sequence[1:], 1):

        if (pattern.start() != sequence[i - 1].end()):
            temp_count = 0

        temp_count += 1
        final_count[keynumber] = max(temp_count, final_count[keynumber])

# Compare the STR counts against each row in the CSV file and print the matching name
for row in data:
    count_match = 0
    for i, key in enumerate(keys):
        if int(row[key]) == final_count[i]:
            count_match += 1
            if count_match == len(keys):
                print(row["name"])
                exit(0)
print("No match")