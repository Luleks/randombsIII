import sympy

def rabin_karp(target_string: str, pattern: str, alphabet: dict):

    alphabet_size = len(alphabet)
    n = len(target_string)
    m = len(pattern)
    q = sympy.prevprime((2 ** 64 - 1) // alphabet_size)
    h = (alphabet_size ** (m - 1)) % q
    p = 0
    t = 0

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
                print(ind)
        t = (alphabet_size * (t - h * alphabet[target_string[ind]]) + alphabet[target_string[i]]) % q
        ind += 1

    if p == t:
        j = 0
        while j < m and target_string[ind + j] == pattern[j]:
            j += 1
        if j == m:
            print(ind)
    

ascii_dict = {chr(i):i for i in range(128)}

rabin_karp('Ovo je targetarget string target', 'target', ascii_dict)
