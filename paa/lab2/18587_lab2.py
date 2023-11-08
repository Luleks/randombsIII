import sympy
import time
import random
import math


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


# cases = [(target_string, pattern, alphabet)]
def test_rabin_karp(cases: list[tuple]):

    with open('report.txt', 'w+') as f:
        for case in cases:
            target_string, pattern, alphabet = case
            start_time = time.perf_counter()

            indexes = rabin_karp(target_string, pattern, alphabet['alphabet'])

            end_time = time.perf_counter()
            total_time = end_time - start_time

            f.write(f'{alphabet["name"]} len(target_string)={len(target_string.split(" ")) - 1} '\
                    f'len(pattern)={len(pattern)} total_time={total_time:.3f}s '\
                    f'Pojavljivanja: {indexes}. Br pojavljivanja {len(indexes)}\n')


# cases = [(str1, str2, alphabet)]
def test_levenhstein(cases: list[tuple]):

    with open('reportLevenhstein.txt', 'w+') as f:
        with open('manjeOdTri.txt', 'w+') as t:
            for case in cases:
                str1, str2, alphabet = case
                words = str1.split(' ')
                three_or_less = []
                
                start_time = time.perf_counter()

                for i, word in enumerate(words):
                    if levenshtein(word, str2) <= 3:
                        three_or_less.append(word)
                
                end_time = time.perf_counter()
                total_time = end_time - start_time
                f.write(f'{alphabet["name"]} len(target_string)={len(words) - 1} '\
                        f'len(pattern)={len(str2)} total_time={total_time:.3f}s\n')
                
                t.write(f'len(target_string)={len(words) - 1}. Pattern: {str2}. <=3: {len(three_or_less)}\n')
                n_iter = len(three_or_less) // 10
                for i in range(n_iter):
                    t.write(f'{three_or_less[i: 10 + 10 * i]}\n')
                t.write(f'{three_or_less[n_iter * 10:]}\n')
                t.write('-' * 30 + '\n')


if __name__ == '__main__':
    # Rabin Karp
    alphabets_with_sep = {'ascii': {chr(i):i for i in range(128)},
                 'hex': {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, 
               '6': 6, '7': 7, '8': 8, '9': 9, 'A': 10, 'B': 11, 
               'C': 12, 'D': 13, 'E': 14, 'F': 15, ' ': 16}}
    
    alphabets = {'ascii': {chr(i):i for i in range(128) if chr(i) != ' '},
                 'hex': {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, 
               '6': 6, '7': 7, '8': 8, '9': 9, 'A': 10, 'B': 11, 
               'C': 12, 'D': 13, 'E': 14, 'F': 15}}

    pattern_sizes = [5, 10, 20, 50]
    
    sizes = [100, 1000]

    cases = []
    for name, alphabet in alphabets.items():
            for size in sizes:
                file = f'{name}_{size}.txt'
                with open(file, 'r') as f:
                    target_string = f.read()
                    
                    patterns = [''.join(random.choice(list(alphabet.keys())) for _ in range(size)) for size in pattern_sizes]
                    for pattern in patterns:
                        cases.append((target_string, pattern, {'name': name, 'alphabet': alphabets_with_sep[name]}))
    
    test_rabin_karp(cases)

    # Levenhstein
    cases = []
    for name, alphabet in alphabets.items():
            for size in sizes:
                file = f'{name}_{size}.txt'
                with open(file, 'r') as f:
                    target_string = f.read()
                    
                    patterns = [''.join(random.choice(list(alphabet.keys())) for _ in range(size)) for size in pattern_sizes]
                    for pattern in patterns:
                        cases.append((target_string, pattern, {'name': name, 'alphabet': alphabets_with_sep[name]}))
    test_levenhstein(cases)
