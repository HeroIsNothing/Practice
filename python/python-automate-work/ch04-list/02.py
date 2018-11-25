if __name__ == '__main__':
    cat_tom = ['fat', 'black', 'loud']
    size, color, disposition = cat_tom
    print(size)
    print(color)
    print(disposition)
    print('-' * 10)

    cat_list = []
    cat_list += ['tom']
    print(cat_list)
    cat_list *= 2
    print(cat_list)
    
    cat_list.append('jerry')
    print(cat_list)

    cat_list.insert(1, 'duck')
    print(cat_list)

    cat_list.remove('tom')
    print(cat_list)

    cat_list.sort()
    print(cat_list)
    print('-' * 10)

    num_string = "0123456789"
    print(num_string[:])
    print(num_string[0:])
    print(num_string[1:4])
    print(num_string[1:-1])
    print('-' * 10)

    list_a = []
    tuple_a = ('cat', 'dog', 5)
    print(list_a)
    print(tuple_a)

    list_a = list(tuple_a)
    print(list_a)

    tuple_b = ('b',)
    print(tuple_b)
    tuple_b = tuple(list_a)
    print(tuple_b)
    print('-' * 10)

    spam = [0, 1, 2, 3, 4, 5]
    cheese = spam
    cheese[1] = 'hello'
    print(cheese)
    print(spam)

    import copy
    spam_2 = [0, 1, 2, 3, 4, 5]
    cheese_2 = copy.copy(spam_2)
    cheese_2[1] = 'hello'
    print(spam_2)
    print(cheese_2)
    print('-' * 10)

    src_list = [[0, 1, 2], [3, 4, 5]]
    print(src_list)
    dst_list = copy.copy(src_list)
    dst_list[0][0] = 'world'
    print(src_list)
    print(dst_list)
    print('')

    src_list = [[0, 1, 2], [3, 4, 5]]
    dst_list = copy.deepcopy(src_list)
    dst_list[0][0] = 'world'
    print(src_list)
    print(dst_list)

    import sys
    sys.exit(0)