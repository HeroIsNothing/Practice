#!/bin/bash
minicom -b 9600 -D /dev/serial0 -o -w -H | ./read_stdin
