import random

letters_ascii = [chr(i) for i in range(128)]
letters_hex = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F']

alphabets = {'ascii': letters_ascii, 'hex': letters_hex}
sizes = [100, 1000, 10_000, 100_000]


for size in sizes:
    for name, alphabet in alphabets.items():

        with open(f'{name}_{size}.txt', 'w+', encoding='ascii') as f:
            for _ in range(size):
                word_length = random.randint(1, 100)
                random_word = ''.join(random.choice(alphabet) for _ in range(word_length))
                f.write(f'{random_word} ')
