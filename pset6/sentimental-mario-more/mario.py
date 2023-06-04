# Prompt for height
while True:
    try:
        height = int(input('Height: '))
        if height > 0 and height < 9:
            break
    except ValueError:
        print('Enter an integer between 1 to 8')

# Build Pyramid
for i in range(height):
    print(
        ' ' * (height - i - 1),
        '#' * (i + 1),
        '  ',
        '#' * (i + 1),
        sep=''
    )