from cs50 import get_string


def main():
    # Getting user input
    t = get_string('Text: ')

    # Count letters
    letters = count_letters(t)

    # Count words
    words = count_words(t) + 1

    # Count sentences
    sentences = count_sentences(t)

    # Implement Coleman-Liau Index
    L = (letters / words) * 100.00
    S = (sentences / words) * 100.00
    index = round(0.0588 * L - 0.296 * S - 15.8)

    # Print Grade
    if (index > 16):
        print('Grade 16+')
    elif (index < 1):
        print('Before Grade 1')
    else:
        print(f'Grade {index}')


def count_letters(t):
    nletters = 0
    for i in t:
        if (i.isalpha()):
            nletters += 1
        else:
            nletters += 0
    return nletters


def count_words(t):
    nwords = 0
    for i in t:
        if (i.isspace()):
            nwords += 1
        else:
            nwords += 0
    return nwords


def count_sentences(t):
    nsentences = 0
    for i in t:
        if (i == '.' or i == '!' or i == '?'):
            nsentences += 1
        else:
            nsentences += 0
    return nsentences


main()