#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  03.py
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
	space= ' '
	
	for i in range(1, 10):
		for j in range(1, 10):
			# Auto ident
			if j != 1:
				if i * j < 10:
					print(space * 3, end='')
				elif i * j < 100:
					print(space * 2, end='')
			# Print value
			print(i * j, end='')
			
		print('')
	
	print('---------------------------------------')
	
	i = 1
	while i < 10:
		j = 1
		while j < 10:
			# Auto ident
			if j != 1:
				if i * j < 10:
					print(space * 3, end='')
				else:
					print(space * 2, end='')
			print(i * j, end='')
			j += 1
		print('')
		i += 1
	
	import sys
	sys.exit(main(sys.argv))
