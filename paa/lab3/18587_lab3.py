def police_thieves(niz: list, k: int):
    niz = sorted([(char, i) for i, char in enumerate(niz)])

    police = next((index for index, (letter, _) in enumerate(niz) if letter == 'P'), None)
    thief = next((index for index, (letter, _) in enumerate(niz) if letter == 'T'), None)

    if police is None or thief is None:
        return 0
    
    last_police = thief - 1
    last_thief = len(niz) - 1

    thieves_caught = 0

    while police <= last_police and thief <= last_thief:
        if abs(niz[police][1] - niz[thief][1]) <= k:
            police += 1
            thief += 1
            thieves_caught += 1
        elif niz[police][1] < niz[thief][1]:
            police += 1
        else:
            thief += 1

    return thieves_caught    


if __name__ == '__main__':
    test_case1 = [['P', 'T', 'T', 'P', 'T'], 1]
    assert(police_thieves(*test_case1) == 2)

    test_case2 = [['T', 'T', 'P', 'P', 'T', 'P'], 2]
    assert(police_thieves(*test_case2) == 3)

    test_case3 = [['P', 'T', 'P', 'T', 'T', 'P'], 3]
    assert(police_thieves(*test_case3) == 3)
