#!/bin/bash

gcc -c *.c
rm lexer.o
rm create_map.o
gcc *.o lexer.c -o lexer