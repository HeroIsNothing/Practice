if __name__ == '__main__':
    allGuests = {
        'Alice': {'apples': 5, 'pretzels': 12},
        'Bob'  : {'ham sandwiches': 3, 'apples': 2},
        'Carol': {'cups': 3, 'apple pies': 1}
    }
    print('')
    print('Number of things being brought: ')
    fruits = {}
    fruit_max_len = 0
    for guest_val in allGuests.values():
        for k, v in guest_val.items():
            fruits.setdefault(k, 0)
            fruits[k] += v
            len_k = len(k)
            if len_k > fruit_max_len:
                fruit_max_len = len_k
    
    for k, v in fruits.items():
        print(' -', k.ljust(fruit_max_len, ' '), v)


    import sys
    sys.exit(0)