if __name__ == '__main__':
    while True:
        print('Enter your age: ', end='')
        age = input()
        if age.isdecimal():
            break
        print('Please enter a NUMBER for your age!')
    
    while True:
        print('Enter your password: ', end='')
        pswd = input()
        if pswd.isalnum():
            break
        print('Password should only have letters and numbers!')
    
    print('Finish')
    
    import sys
    sys.exit(0)