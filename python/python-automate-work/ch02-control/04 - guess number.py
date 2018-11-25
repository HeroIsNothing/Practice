if __name__ == '__main__':

    import random
    quite_game = False
    game_no = 1
    while not quite_game:
        print('--------- Round ' + str(game_no) + ' ----------')
        print('Guess a number in [1, 10]')

        val_target = random.randint(1, 10)
        while True:
            print(">> ", end='')
            val_input = int(input())
            if val_target == val_input:
                print("That's it!")
                break
            elif val_target < val_input:
                print('Guess lower.')
            else:
                print('Guess larger.')

        print('Play again(y/n)? ', end='')
        val_confirm = input()
        if val_confirm.upper() == 'N':
            quite_game = True
        else:
            game_no += 1

    print('Good bye!')

    import sys
    sys.exit(100)   # echo $? will return 100
