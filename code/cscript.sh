#!/bin/bash

gcc -c *.c
rm driver.o
rm create_map.o
gcc -g *.o driver.c -o driver
./driver
rm driver
rm *.o