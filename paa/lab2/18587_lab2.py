import sympy
import time


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

    with open('RK_report.txt', 'w+') as f:
        with open('RK_indeksi.txt', 'w+') as t:
            for case in cases:
                target_string, pattern, alphabet = case
                start_time = time.perf_counter()

                indexes = rabin_karp(target_string, pattern, alphabet['alphabet'])

                end_time = time.perf_counter()
                total_time = end_time - start_time


                f.write(f'{alphabet["name"]} len(target_string)={len(target_string.split(" ")) - 1} '\
                        f'len(pattern)={len(pattern)} br_pojavljivanja: {len(indexes)} total_time={total_time:.3f}s\n')
                
                t.write(f'len(target_string)={len(target_string.split(" ")) - 1}. Pattern: {pattern}. Br_pojava: {len(indexes)}\n')
                n_iter = len(indexes) // 10
                for i in range(n_iter):
                    t.write(f'{indexes[10 * i: 10 + 10 * i]}\n')
                if len(indexes) % 10 != 0:
                    t.write(f'{indexes[n_iter * 10:]}\n')
                t.write('-' * 30 + '\n')


# cases = [(str1, str2, alphabet)]
def test_levenhstein(cases: list[tuple]):

    with open('LE_report.txt', 'w+') as f:
        with open('LE_words.txt', 'w+') as t:
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
                        f'len(pattern)={len(str2)} br_reci={len(three_or_less)} total_time={total_time:.3f}s\n')
                
                t.write(f'len(target_string)={len(words) - 1}. Pattern: {str2}. Br reci sa udaljenih <= 3: {len(three_or_less)}\n')
                n_iter = len(three_or_less) // 10
                for i in range(n_iter):
                    t.write(f'{three_or_less[10 * i: 10 + 10 * i]}\n')
                if len(three_or_less) % 10 != 0:
                    t.write(f'{three_or_less[n_iter * 10:]}\n')
                t.write('-' * 30 + '\n')


if __name__ == '__main__':
    # Rabin Karp
    alphabets = {'ascii': {chr(i):i for i in range(255)},
                 'hex': {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, 
               '6': 6, '7': 7, '8': 8, '9': 9, 'A': 10, 'B': 11, 
               'C': 12, 'D': 13, 'E': 14, 'F': 15, ' ': 16}}

    patterns_sizes = [5, 10, 20, 50]
    patterns = {'ascii': ['OpQrS', 'thislen10!', 'thislen10not10but20!', 'thislen10not10but20not20but50ThIsLon2~@#!~!./,*-//'],
                'hex': ['12345', 'A987654321', '1234456789AABCDEF0DD', '5D3E0C9B1D7A5F4C2E8A3B4D6F9E1ADD0FEDCBBAA987654321']}

    sizes = [100, 1000, 10000, 100000]

    cases = []
    for name, alphabet in alphabets.items():
            for size in sizes:
                file = f'{name}_{size}.txt'
                with open(file, 'r', encoding='utf-8') as f:
                    target_string = f.read()
                    for pattern in patterns[name]:
                        cases.append((target_string, pattern, {'name': name, 'alphabet': alphabets[name]}))
    
    test_rabin_karp(cases)

    # Levenhstein
    cases = []
    for name, alphabet in alphabets.items():
            for size in sizes:
                file = f'{name}_{size}.txt'
                with open(file, 'r', encoding='utf-8') as f:
                    target_string = f.read()
                    for pattern in patterns[name]:
                        cases.append((target_string, pattern, {'name': name, 'alphabet': alphabets[name]}))
    test_levenhstein(cases)
