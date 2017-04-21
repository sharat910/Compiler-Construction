#!/bin/bash
nasm -f elf64 assembly.asm
ld -m elf_x86_64 -s -o run assembly.o -lc
./run