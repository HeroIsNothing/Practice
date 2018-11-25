if __name__ == '__main__':
    birthdays = {'Alice': '04-01',
                 'Bob'  : '12-12',
                 'Carol': '03-04'}
    while True:
        print('Enter a name: (blank to quit)')
        name = input()
        if name == ' ':
            break
        
        if name in birthdays:
            print(birthdays[name], ' is the birthday of ', name)
        else:
            print('We don\'t have your birthday, \nplease enter it: ', end='')
            bday = input()
            birthdays[name] = bday
            print('Birthday database updated.')
    print('-' * 10)

    # Display birthday map
    for k, v in birthdays.items():
        print(k.ljust(7, ' '), ': ', v)
    
    import sys
    sys.exit(0)