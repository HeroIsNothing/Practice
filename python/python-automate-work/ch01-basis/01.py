#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  01.py
#  
#  Copyright 2018  <pi@raspberrypi>
#  
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#  
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#  
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
#  MA 02110-1301, USA.
#  
#  


def main(args):
    return 0

if __name__ == '__main__':
    import sys
    
    print('Alice' + 'Bob')
    print('Alice' * 5);
    #print('Alice' + 5); #error!
    print('-------------');
    
    '''
    print('What is your name?');
    name = input();
    print('It is good to meet you ' + name);
    print('The length of your name is: ' + str(len(name)));
    print("What is your age?");
    age = input();
    print("You'll be " + str(int(age) + 1) + ' in a year.');
    '''
    a = 10;
    b = 2;
    c = 3;
    print(a/b);
    print(a/c);
    
    print(a/float(b));
    print(a/float(c));
    
    print(int(a)/int(b));
    print('-----------------');
    
    print(1/2);
    
    
    
    
    sys.exit(main(sys.argv))
