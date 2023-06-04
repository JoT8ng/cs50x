from cs50 import get_int


# Prompt for height
while True:
    height = get_int('Height: ')
    if height > 0 and height < 9:
        break

# Build Pyramid
for i in range(height):
    print(
        ' ' * (height - i - 1),
        '#' * (i + 1),
        sep=''
    )