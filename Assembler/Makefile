# A makefile for compiling the LabelTable test driver, a secondary test
# driver that simulates pass 1 of an assembler, a test driver for testing
# printing machine code components in binary, and the final assembler.
# The makefile also compiles a simple tool (stripCR) for stripping Windows
# carriage returns from assembler output for comparison with a provided
# sample output file.

GCC=gcc -Wall -Wextra -Wpedantic -Wformat -Wshadow -Wredundant-decls \
    -Wstrict-prototypes
# Can also use -Wtraditional or -Wmissing-prototypes

#  Switch to alternative version of the all target when working on assembler.
# all:	testLabelTable testPass1
all:	testLabelTable testPass1 testPrintAsBinary assembler stripCR

assembler.h:	LabelTableArrayList.h getToken.h \
		printFuncs.h process_arguments.h names.h same.h
	touch assembler.h

testLabelTable:	assembler.h \
		LabelTableArrayList.c \
		process_arguments.c \
		printDebug.c \
		printError.c \
		same.c \
		testLabelTable.c
	$(GCC) -g process_arguments.c printDebug.c printError.c same.c \
		LabelTableArrayList.c \
	    	testLabelTable.c -o testLabelTable

testPass1: 	assembler.h \
		LabelTableArrayList.c \
		process_arguments.c \
		getToken.c \
		pass1.c \
		printDebug.c \
		printError.c \
		same.c \
		testPass1.c
	$(GCC) -g process_arguments.c printDebug.c printError.c same.c \
		pass1.c getToken.c \
		LabelTableArrayList.c \
		testPass1.c -o testPass1

testPrintAsBinary:	assembler.h \
			printAsBinary.c \
			LabelTableArrayList.c \
			printDebug.c \
			printError.c \
			registerNames.c \
			same.c \
			testPrintAsBinary.c
	$(GCC) -g process_arguments.c printDebug.c printError.c same.c \
		LabelTableArrayList.c \
		registerNames.c \
		printAsBinary.c \
		testPrintAsBinary.c -o testPrintAsBinary

assembler: 	assembler.h \
		LabelTableArrayList.c \
		process_arguments.c \
		instructionNames.c \
		registerNames.c \
		getInstName.c \
		getToken.c \
		getNTokens.c \
		pass1.c \
		pass2.c \
		printAsBinary.c \
		printDebug.c \
		printError.c \
		same.c \
		assembler.c
	$(GCC) -g process_arguments.c printDebug.c printError.c same.c \
		pass1.c pass2.c getToken.c getNTokens.c getInstName.c \
		LabelTableArrayList.c \
		instructionNames.c registerNames.c \
		printAsBinary.c \
		assembler.c -o assembler

stripCR:	assembler.h \
		process_arguments.h \
		printDebug.c \
		printError.c \
		process_arguments.c \
		same.c \
		stripCR.c
	$(GCC) -g process_arguments.c printDebug.c printError.c same.c \
		stripCR.c -o stripCR

clean: 
	rm -rf testLabelTable testPass1 testPrintAsBinary assembler stripCR
