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
	
	access_granted = False
	while not access_granted:
		print("Who are you?");
		
		name = input();
		if name != "Ronie":
			print("   go away!");
			continue;
		
		while True:
			print("Hello " + name + ". What is the password? (It is a fish.)");
			pswd = input();
			if pswd == "swordfish":
				access_granted = True;
				break;
	print("Acess granted.");

	sys.exit(main(sys.argv))
