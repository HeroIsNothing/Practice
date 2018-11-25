def concat_str(str_org, str_new):
    return str_org + str_new

def say_hello():
    print('hello')

def check_isNone(val):
    if None == val:
        print('<None>')
    else:
        print('<not None>')

eggs = 'global'
def spam():
    # print(eggs) # error!
    # global eggs
    eggs = 'spam'

def devide_by(a, b):
    try:
        return a / b
    except ZeroDivisionError:
        print('Error: divided by 0!')

if __name__ == '__main__':
    val = concat_str('hello ', 'world')
    check_isNone(val)

    val = print(val)
    check_isNone(val)

    val = say_hello()
    check_isNone(val)
    print('-' * 10)

    print('cat', 'dog', 'bog')
    print('cat', 'dog', 'bog', sep=', ')
    print('-' * 10)

    print(eggs)
    spam()
    print(eggs)
    print('-' * 10)

    print(devide_by(10, 2))
    print(devide_by(10, 0))
    print(10 / 0)

    import sys
    sys.exit(0)