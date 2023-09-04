from cs50 import get_int

height = 0

# Ask user to enter the height of desired pyramid
while height < 1 or height > 8:
    height = get_int("Height: ")

# Print left pyramid
for c in range(height):
    for r in range(height):
        if (r < height - c - 1):
            print(" ", end="")
        else:
            print("#", end="")
            
    # Print space between pyramid        
    print("  ", end="")
    
    # Print right pyramid
    for r in range(c + 1):
        print("#", end="")
    print()