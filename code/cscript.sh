#!/bin/bash

gcc -c *.c
rm driver.o
rm create_map.o
gcc *.o driver.c -o driver
./driver > map_population.txt