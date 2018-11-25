if __name__ == '__main__':
    import pprint
    messages = 'It was a bright code day in April, and the clocks were striking'

    count = {}

    for ch in messages:
        count.setdefault(ch, 0)
        count[ch] += 1

    pprint.pprint(count)
    count_z = count.get('z', 0)
    print(count_z)

    import sys
    sys.exit(0)