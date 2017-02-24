#!/bin/bash

gcc -c *.c
rm lexer.o
gcc *.o lexer.c -o lexer