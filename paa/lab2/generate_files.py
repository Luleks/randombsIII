import random
import nltk
from nltk.corpus import words
import string
import time
random.seed(time.time())


nltk.download('words')

word_list = words.words()
punct = string.punctuation
ascii_dope = ['OpQrS', 'thislen10!', 'thislen10not10but20!', 'thislen10not10but20not20but50ThIsLon2~@#!~!./,*-//']

letters_hex = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F']
hex_dope = ['12345', 'A987654321', '1234456789AABCDEF0DD', '5D3E0C9B1D7A5F4C2E8A3B4D6F9E1ADD0FEDCBBAA987654321']

sizes = [100, 1000, 10_000, 100_000]
pattern_sizes = [5, 10, 20, 50]


for size in sizes:
    choices = random.sample(word_list, size)

    with open(f'ascii_{size}.txt', 'w+', encoding='utf-8') as f:
        for _ in range(size):
            if random.uniform(0, 1) < 0.1:
                random_word = random.choice(ascii_dope)
            else:
                random_word = random.choice(choices)

            if random.uniform(0, 1) < 0.6:
                f.write(f'{random_word} ')
            else:
                f.write(f'{random_word}{random.choice(punct)} ')

for size in sizes:

    with open(f'hex_{size}.txt', 'w+', encoding='utf-8') as f:
        for _ in range(size):
            if random.uniform(0, 1) < 0.1:
                random_word = random.choice(hex_dope)
            else:
                word_length = random.randint(1, 100)
                random_word = ''.join(random.choice(letters_hex) for _ in range(word_length))

            f.write(f'{random_word} ')
