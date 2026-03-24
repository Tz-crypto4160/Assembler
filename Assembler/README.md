# MIPS Two-Pass Assembler
Author: Taiki Sawamata 03/2026

## Description
This program is a two-pass assembler for the MIPS architecture, written in C. It reads a text file containing MIPS assembly language instructions and translates them into 32-bit pseudo-binary machine code (strings consisting of '0' and '1' characters). 

During the **first pass**, it scans the code to find all instruction labels and records their memory addresses in a label table. During the **second pass**, it uses this table to resolve branch offsets and jump targets, parsing each instruction to output its exact machine code format (R, I, or J type). This tool is highly useful for understanding how human-readable assembly is encoded into machine-readable formats.

## How to Compile
A `Makefile` is provided to easily compile the program. Open your terminal in the project directory and run the following commands:

make clean
make assembler

This will generate an executable file named `assembler`.

## How to Run
Run the executable from the command line, providing the MIPS assembly file as an argument:

./assembler <filename>

**Example:**
./assembler myTestfile.mips

*(Note: You can redirect the output to a file using `./assembler myTestfile.mips > output.txt`)*

## Sample Input
Here is a small sample of MIPS assembly code:
main:   addi $t0, $zero, 5
        beq  $t0, $zero, finish
        j    main
finish: add  $v0, $t0, $zero

## Sample Output
Given the input above, the program will output the corresponding 32-bit machine language instructions:
00100000000010000000000000000101
00010001000000000000000000000001
00001000000000000000000000000000
00000001000000000001000000100000

## Note:
This project was developed as part of the CS 315 (Computer Organization) course at Kalamazoo College.


