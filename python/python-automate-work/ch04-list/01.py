if __name__ == '__main__':
    player_list = ['Ronaldo', 'Owen', 'Raul', 'Zidane', 'Figo', 'Carlos']
    for player in player_list:
        print(player, end=', ')
    print('')

    for i in range(0, len(player_list)):
        if i != len(player_list)-1:
            print(player_list[i], end='; ')
        else:
            print(player_list[i])
    print('')

    print(player_list[1:4])
    print(player_list[1:-1])
    print('')

    print(player_list[0:])
    print(player_list[0:-1])
    print('')

    print(player_list[:])
    print(player_list[:-1]) 
    print('')

    import random
    rand_list = []
    for i in range(20):
        rand_list += [random.randint(1, 100)]    # Concatenate lists
    print('before: ', rand_list)

    for i in range(len(rand_list)-1, -1, -1):
        if rand_list[i] % 2 == 0:
            del rand_list[i]
    print('after:  ', rand_list)
    print('')

    # use "string in string"
    sentence = 'hello world stupid vi who is this guy'
    word_check_list = ['stupid', 'foolish']
    for word in word_check_list:
        if word in sentence:
            print('sentence contains: ', word)
        else:
            print("sentence doesn't contain: ", word )
    print('')

    # use "string in list"
    sentence_list = sentence.split(' ')
    print(sentence_list)
    for word in sentence_list:
        if word in word_check_list:
            print(word.ljust(7, ' '), ' is in the check list.')
        else:
            print(word.ljust(7, ' '), ' is not in the check list.')
    print('')

    import sys
    sys.exit(0)
