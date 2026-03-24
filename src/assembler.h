/*
 * This file includes common system header files, several local header
 * files widely used in the assembler program, and signatures for other
 * commonly used functions.
 */

#ifndef _ASSEMBLER_H
#define _ASSEMBLER_H

#include <stdio.h>
#include <stdlib.h>     /* May need to be _stdlib.h on some machines. */
#include <string.h>	/* Might be memory.h on some machines. */
#include <ctype.h>

#include "LabelTableArrayList.h"  /* Label Table functions */
#include "getToken.h"   /* function to parse input tokens */
#include "printFuncs.h" /* functions for printing debugging/error msgs */
#include "process_arguments.h"   /* process command-line arguments */
#include "names.h"      /* functions re: instruction and register names */
#include "same.h"       /* defines SAME for use with strcmp */

LabelTableArrayList pass1 (FILE * fp);
void pass2 (FILE * fp, LabelTableArrayList * table);

int getNTokens (char * instructionBuffer, int N, char * results[]);
void getInstName(char * input, char ** instrName, char **restOfLine);

void processIorJ(int lineNum, LabelTableArrayList * table,
                 int opcode, char * restOfInstruction, int PC);
void processR(int lineNum, int functCode, char * restOfInstruction);

void printInt(int value, int length);
void printReg(char * regName, int lineNum);
void printSignedIntInString(char * intInString, int numBits, int lineNum);
void printUnsignedIntInString(char * intInString, int numBits, int lineNum);
void printJumpTarget(char * targetLabel, LabelTableArrayList * table,
                     int lineNum);
void printBranchOffset(char * targetLabel, LabelTableArrayList * table,
                       int PC, int lineNum);

#endif
