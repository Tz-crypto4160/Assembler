/*
 * This file contains two static global arrays -- one containing I and
 * J format MIPS instructions, and one containing R format MIPS
 * instructions.  It also contains functions that associate instruction
 * names with their appropriate opcodes (I/J format)  or funct codes (R format).
 *
 * Author: Taiki Sawamata
 *    (based on a skeleton by Alyce Brady,
 *          with ideas from Autumn Spaulding Winter 99
 *          and Jackson Kiino-Terburg Winter 22)
 * Date:   3/22/2022
 *
 *    Modified:  01/11/2026
 *
 * 
 */

#include <string.h>
#include "names.h"
#include "same.h"

/* Create a static (persistent) array of the mnemonic names of I and J
 * format instruction names.  The array is a "static global" variable,
 * meaning it is available to any functions defined in this file, but only
 * in this file. (In this context, "static" means its scope is limited to
 * this file).
 */
static char * ijFormatInstructions[] =
{
    "",      "",       "j",     "jal",  "beq",       /* 0 to 4 */
    "bne",   "",       "",      "addi", "addiu",     /* 5 to 9 */
    "slti",  "sltiu",  "andi",  "ori",   "",         /* 10 to 14 */
    "lui",   "",       "",      "",      "",         /* 15 to 19 */
    "",      "",       "",      "",      "",         /* 20 to 24 */
    "",      "",       "",      "",      "",         /* 25 to 29 */
    "",      "",       "",      "",      "",         /* 30 to 34 */
    "lw",    "",       "",      "",      "",         /* 35 to 39 */
    "",      "",       "",      "sw"                 /* 40 to 43 */
};

/* Define a named constant for the number of entries in
 * ijFormatInstructions.  (The number of meaningful instructions is less,
 * because some entries are empty strings (""), but this is the number of
 * entries in the array.)
 */
const int NUM_IJ_INSTRUCTIONS = 44;

/* Create a static (persistent) array of the mnemonic names of R format
 * instruction names.  The array is a "static global" variable, meaning it
 * is available to any functions defined in this file, but only in this
 * file. (In this context, "static" means its scope is limited to this
 * file).
 */
static char * rFormatInstructions[] =
{
    "sll",  "",     "srl",  "",     "",         /* 0 to 4 */
    "",     "",     "",     "jr",   "",         /* 5 to 9 */
    "",     "",     "",     "",     "",         /* 10 to 14 */
    "",     "",     "",     "",     "",         /* 15 to 19 */
    "",     "",     "",     "",     "",         /* 20 to 24 */
    "",     "",     "",     "",     "",         /* 25 to 29 */
    "",     "",     "add",  "addu", "sub",      /* 30 to 34 */
    "subu", "and",  "or",   "",     "nor",      /* 35 to 39 */
    "",     "",     "slt",  "sltu"              /* 40 to 43 */
};

/* Define a named constant for the number of entries in
 * rFormatInstructions.  (The number of meaningful instructions is less,
 * because some entries are empty strings (""), but this is the number of
 * entries in the array.)
 */
const int NUM_R_INSTRUCTIONS = 44;

/*
 * This function looks up and returns the instruction name for a given
 * opcode.
 *     @param  opcode  the opcode for an I or J format MIPS instruction
 *     @return a pointer to a string containing the instruction name or
 *             an empty string if opcode is not a recognized, valid opcode
 */
char * getIJInstName (int opcode)
{
    if ( opcode >= 0 && opcode < NUM_IJ_INSTRUCTIONS )
        return ijFormatInstructions[opcode];
    else
        return "";
}

/*
 * This function looks up and returns the instruction name for a given
 * funct code.
 *     @param  funct  the funct code for an R format MIPS instruction
 *     @return a pointer to a string containing the instruction name or
 *             an empty string if funct is not a recognized, valid funct code
 */
char * getRInstName (int funct)
{
    if ( funct >= 0 && funct < NUM_R_INSTRUCTIONS)
        return rFormatInstructions[funct];
    else
        return "";     
}

/*
 * This function looks up and returns the opcode for a given
 * instruction name.
 *    @param instrName      name of instruction (input)
 *    @return  the opCode if instrName is a valid I or J format instruction,
 *             or 0 (i.e., if instrName is either a valid R format instruction
 *             or is not a valid instruction of any format)
 */
int getOpCode(char * instrName)
{
    int i;

    for (i = 0; i < NUM_IJ_INSTRUCTIONS; i++) 
    {
        if (strcmp(instrName, ijFormatInstructions[i]) == SAME )
            return i;
    }

    return 0;    /* If not found, opcode is assumed to be R format (or invalid). */
}

/*
 * This function looks up and returns the funct code for a given
 * instruction name.
 *    @param instrName      name of instruction (input)
 *    @return  the funct code if instrName is a valid R format instruction,
 *             or -1 if instrName is not a valid R format instruction
 */
int getFunctCode(char * instrName)
{
    int i;

    for (i = 0; i < NUM_R_INSTRUCTIONS; i++) /*search the list of r format*/
    { 

        if (strcmp(instrName, rFormatInstructions[i]) == SAME) /*if correct, return that index(Funct)*/
            return i;
    }

    return -1;     /* If not found, opcode is assumed to be invalid. */
}


