# Directory settings
SRC_DIR = src

GCC=gcc -Wall -Wextra -Wpedantic -Wformat -Wshadow -Wredundant-decls \
    -Wstrict-prototypes -I$(SRC_DIR)

all: testLabelTable testPass1 testPrintAsBinary assembler stripCR

# Helper for header dependency
$(SRC_DIR)/assembler.h: $(SRC_DIR)/LabelTableArrayList.h $(SRC_DIR)/getToken.h \
                        $(SRC_DIR)/printFuncs.h $(SRC_DIR)/process_arguments.h \
                        $(SRC_DIR)/names.h $(SRC_DIR)/same.h
	touch $(SRC_DIR)/assembler.h

testLabelTable: $(SRC_DIR)/assembler.h \
                $(SRC_DIR)/LabelTableArrayList.c \
                $(SRC_DIR)/process_arguments.c \
                $(SRC_DIR)/printDebug.c \
                $(SRC_DIR)/printError.c \
                $(SRC_DIR)/same.c \
                $(SRC_DIR)/testLabelTable.c
	$(GCC) -g $(SRC_DIR)/process_arguments.c $(SRC_DIR)/printDebug.c \
		$(SRC_DIR)/printError.c $(SRC_DIR)/same.c \
		$(SRC_DIR)/LabelTableArrayList.c \
		$(SRC_DIR)/testLabelTable.c -o testLabelTable

testPass1: $(SRC_DIR)/assembler.h \
           $(SRC_DIR)/LabelTableArrayList.c \
           $(SRC_DIR)/process_arguments.c \
           $(SRC_DIR)/getToken.c \
           $(SRC_DIR)/pass1.c \
           $(SRC_DIR)/printDebug.c \
           $(SRC_DIR)/printError.c \
           $(SRC_DIR)/same.c \
           $(SRC_DIR)/testPass1.c
	$(GCC) -g $(SRC_DIR)/process_arguments.c $(SRC_DIR)/printDebug.c \
		$(SRC_DIR)/printError.c $(SRC_DIR)/same.c \
		$(SRC_DIR)/pass1.c $(SRC_DIR)/getToken.c \
		$(SRC_DIR)/LabelTableArrayList.c \
		$(SRC_DIR)/testPass1.c -o testPass1

testPrintAsBinary: $(SRC_DIR)/assembler.h \
                   $(SRC_DIR)/printAsBinary.c \
                   $(SRC_DIR)/LabelTableArrayList.c \
                   $(SRC_DIR)/printDebug.c \
                   $(SRC_DIR)/printError.c \
                   $(SRC_DIR)/registerNames.c \
                   $(SRC_DIR)/same.c \
                   $(SRC_DIR)/testPrintAsBinary.c
	$(GCC) -g $(SRC_DIR)/process_arguments.c $(SRC_DIR)/printDebug.c \
		$(SRC_DIR)/printError.c $(SRC_DIR)/same.c \
		$(SRC_DIR)/LabelTableArrayList.c \
		$(SRC_DIR)/registerNames.c \
		$(SRC_DIR)/printAsBinary.c \
		$(SRC_DIR)/testPrintAsBinary.c -o testPrintAsBinary

assembler: $(SRC_DIR)/assembler.h \
           $(SRC_DIR)/LabelTableArrayList.c \
           $(SRC_DIR)/process_arguments.c \
           $(SRC_DIR)/instructionNames.c \
           $(SRC_DIR)/registerNames.c \
           $(SRC_DIR)/getInstName.c \
           $(SRC_DIR)/getToken.c \
           $(SRC_DIR)/getNTokens.c \
           $(SRC_DIR)/pass1.c \
           $(SRC_DIR)/pass2.c \
           $(SRC_DIR)/printAsBinary.c \
           $(SRC_DIR)/printDebug.c \
           $(SRC_DIR)/printError.c \
           $(SRC_DIR)/same.c \
           $(SRC_DIR)/assembler.c
	$(GCC) -g $(SRC_DIR)/process_arguments.c $(SRC_DIR)/printDebug.c \
		$(SRC_DIR)/printError.c $(SRC_DIR)/same.c \
		$(SRC_DIR)/pass1.c $(SRC_DIR)/pass2.c $(SRC_DIR)/getToken.c \
		$(SRC_DIR)/getNTokens.c $(SRC_DIR)/getInstName.c \
		$(SRC_DIR)/LabelTableArrayList.c \
		$(SRC_DIR)/instructionNames.c $(SRC_DIR)/registerNames.c \
		$(SRC_DIR)/printAsBinary.c \
		$(SRC_DIR)/assembler.c -o assembler

stripCR: $(SRC_DIR)/assembler.h \
         $(SRC_DIR)/process_arguments.h \
         $(SRC_DIR)/printDebug.c \
         $(SRC_DIR)/printError.c \
         $(SRC_DIR)/process_arguments.c \
         $(SRC_DIR)/same.c \
         $(SRC_DIR)/stripCR.c
	$(GCC) -g $(SRC_DIR)/process_arguments.c $(SRC_DIR)/printDebug.c \
		$(SRC_DIR)/printError.c $(SRC_DIR)/same.c \
		$(SRC_DIR)/stripCR.c -o stripCR

clean:
	rm -rf testLabelTable testPass1 testPrintAsBinary assembler stripCR
