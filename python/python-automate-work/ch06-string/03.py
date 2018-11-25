#!/usr/bin/python
if __name__ == '__main__':
    cat_list = ['tom', 'jerry']
    cat_str = ' and '.join(cat_list)
    print(cat_list)
    print(cat_str)

    cat_list = []
    print(cat_list)
    cat_list = cat_str.split(' and ')
    print(cat_list)

    import sys
    sys.exit(0)
