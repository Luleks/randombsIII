import sympy
import random
from functools import wraps
import time
from typing import Callable


def exact_match(func: Callable, *args):
    @wraps(func)
    def wrap(*args):
        target_string_word_count = len(args[0].split(' '))
        target_string = args[0].replace(' ', '')
        start_time = time.perf_counter()

        inds = func(target_string, *args[1:])

        end_time = time.perf_counter()
        with open(f'{func.__name__}_{target_string_word_count}_{len(args[1])}.txt', 'w+') as f:
            for ind in inds:
                f.write(f'{ind} ')

        return f'{func.__name__} je izvrsio pattern matching nad stringom duzine {len(target_string)}'\
               f' i patternom duzine {len(args[1])} za {(end_time - start_time):.3f} sekundi'
    return wrap


@exact_match
def rabin_karp(target_string: str, pattern: str, alphabet: dict):

    alphabet_size = len(alphabet)
    n = len(target_string)
    m = len(pattern)
    q = sympy.prevprime((2 ** 64 - 1) // alphabet_size)
    h = (alphabet_size ** (m - 1)) % q
    p = 0
    t = 0

    indexes = []

    for i, letter in enumerate(pattern):
        p = (alphabet_size * p + alphabet[letter]) % q  
        t = (alphabet_size * t + alphabet[target_string[i]]) % q

    ind = 0
    for i in range(m, n):
        if p == t:
            j = 0
            while j < m and target_string[ind + j] == pattern[j]:
                j += 1
            if j == m:
                indexes.append(ind)
        t = (alphabet_size * (t - h * alphabet[target_string[ind]]) + alphabet[target_string[i]]) % q
        ind += 1

    if p == t:
        j = 0
        while j < m and target_string[ind + j] == pattern[j]:
            j += 1
        if j == m:
            indexes.append(ind)

    return indexes


def failure_func(pattern: str) -> list[int]:
    pi = [0] * len(pattern)
    pi[0] = -1
    for i in range(1, len(pattern)):
        j = pi[i - 1]
        while j > 0 and pattern[i] != pattern[j]:
            j = pi[j - 1]
        if pattern[i] == pattern[j]:
            j += 1
        pi[i] = j
    return pi


@exact_match
def knuth_morris_pratt(target_string: str, pattern: str):
    pi = failure_func(pattern)
    j = -1

    indexes = []

    i = 0
    while i < len(target_string):
        if target_string[i] == pattern[j + 1]:
            i += 1
            j += 1        
            if j + 1 == len(pattern):
                indexes.append(i - len(pattern))
                j = pi[j]
        else:
            if j == -1:
                i += 1
            else:
                j = pi[j]
    return indexes

letter_to_number = {
    'b': 1, 'f': 1, 'p': 1, 'v': 1,
    'c': 2, 'g': 2, 'j': 2, 'k': 2, 'q': 2, 's': 2, 'x': 2, 'z': 2,
    'd': 3, 't': 3,
    'l': 4,
    'm': 5, 'n': 5,
    'r': 6
}

def soundEx(string: str):
    neutrals = {'a', 'e', 'i', 'o', 'u', 'y', 'h', 'w'}
    seen = {}
    strng = ''
    for i, letter in enumerate(string):
        if letter in neutrals:
            seen[letter] = i
        elif letter_to_number[letter.lower()] in seen:
            idx = seen[letter_to_number[letter.lower()]]
            if i - idx == 1 or (i - idx == 2 and string[i - 1] in {'h', 'w'}):
                seen[letter_to_number[letter.lower()]] = i
            else:
                strng += letter
        else:
            seen[letter_to_number[letter.lower()]] = i
            strng += letter

    new_string = string[0]
    for i in range(1, len(strng)):
        new_string += str(letter_to_number[strng[i].lower()])

    if len(new_string) < 4:
        new_string += '0' * (4 - len(new_string))
    else:
        new_string = new_string[0:4]
    print(new_string)


def levenshtein(str1: str, str2: str) -> int:
    matrix = [[0] * (len(str2) + 1) for _ in range(len(str1) + 1)]
    
    for i in range(1, len(str1) + 1):
        matrix[i][0] = matrix[i - 1][0] + 1
    for j in range(1, len(str2) + 1):
        matrix[0][j] = matrix[0][j - 1] + 1

    for i in range(len(str1)):
        for j in range(len(str2)):
            if str1[i] == str2[j]:
                inc = 0
            else:
                inc = 1
            matrix[i + 1][j + 1] = min(matrix[i][j] + inc, matrix[i + 1][j] + 1, matrix[i][j + 1] + 1)
    
    return matrix[len(str1)][len(str2)]

# levenshtein('sitting', 'kitten')

# ascii_dict = {chr(i):i for i in range(128)}

# target = 'Ovo je targetarget string target'
# pattern = 'target'

# rabin_karp(target, pattern, ascii_dict)
# knuth_morris_pratt(target, pattern)

letters_ascii = {chr(i):i for i in range(128)}
letters_hex = {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, 
               '6': 6, '7': 7, '8': 8, '9': 9, 'A': 10, 'B': 11, 
               'C': 12, 'D': 13, 'E': 14, 'F': 15}

pattern_sizes = [5, 10, 20, 50]

patterns_ascii = [''.join(random.choice(list(letters_ascii.keys())) for _ in range(size)) for size in pattern_sizes]
patterns_hex = [''.join(random.choice(list(letters_hex.keys())) for _ in range(size)) for size in pattern_sizes]

alphabets = {'hex': (letters_hex, patterns_hex)}
sizes = [100, 1000, 10_000, 100_000]

for size in sizes:
    for name, (alphabet, patterns) in alphabets.items():
        with open(f'{name}_{size}.txt', 'r') as f:
            target_string = f.read()
            for pattern in patterns:
                print(rabin_karp(target_string, pattern, alphabet))
                print(knuth_morris_pratt(target_string, pattern))

