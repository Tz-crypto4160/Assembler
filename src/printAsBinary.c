#include "assembler.h"
#include <stdlib.h>
#include <stdio.h>

/*
 * The functions in this file print pseudo-binary output for:
 *    - integer values, e.g., 23
 *    - integer values represented as strings, e.g., "23"
 *    - registers, e.g., $zero ==> "00000"
 *    - jump targets
 *    - branch offsets
 * The pseudo-binary output actually consists of character 0's and 1's,
 * with the length of the binary output specified by the `numBits`
 * parameter.  The `lineNum` parameter is used when printing error
 * messages.
 *
 * Author(s):
 * Date:
 *      with assistance from:
 *      working side-by-side with:
 * 
 * Modification Log:
 *    - AB, 3/25/2020 - implement printIntInString, stub printInt,
 *                      provide skeletons for others
 *    - AB, 3/1/2022 -  replace previous printIntInString with
 *                      printSignedIntInString and printUnsignedIntInString.
 *                      New internal printIntInString does range checking.
 *    - Taiki Sawamata, 03/10/2026
 *                    - Implemented previously stubbed functions: printInt, printReg, printJumpTarget,
 *                      and printBranchOffset to output correct binary.
 */

 /* Print integer value in pseudo-binary (made up of character '0's and '1's).
 * @param value   value to print in pseudo-binary
 * @param length  length of binary code needed, in bits
 * @pre           value can be represented in `length` number of bits
 * Note: This function uses bitwise operations to correctly handle both 
 * positive and negative (two's complement) integers.
 */

void printInt(int value, int length)
{
    int i;
    for (i = length - 1; i >= 0; i--)
    {
        int bit = (value >> i) & 1;
        printf("%d", bit);
    }
}


/* Print register in pseudo-binary (made up of character '0's and '1's).
 *      @param regName   name of register to print in pseudo-binary
 *      @param lineNum   line number (for error messages)
 * If the register name passed as a parameter is an invalid register name,
 * this function prints "<invalid reg>" instead of the register number,
 * allowing the rest of the instruction to be parsed and printed.
 */
void printReg(char * regName, int lineNum)
{
    int regNbr = getRegNbr(regName);
    if (regNbr == -1) 
    {
    printError("Invalid register name on line %d\n", lineNum);
    printInt(0, 5);
    } 
    else 
    {
    printInt(regNbr, 5);
    }
}

/* Declare internal printIntInString used by both printSignedIntInString
 * and printUnsignedIntInString.
 */
static void printIntInString(char * intInString, int numBits,
        int lowerBound, int upperBound, int lineNum);

/* Print signed value in `intInString` as pseudo-binary (made up of character
 * '0's and '1's).  Prints and error if the token in the string is not a
 * valid integer or if it is not in the range
 * -2^(numBits-1) <= integer < 2^(numBits-1).
 *      @param intInString   string containing integer, e.g., "23"
 *      @param length  length of binary code needed, in bits
 *      @param lineNum line number (for error messages)
 */
void printSignedIntInString(char * intInString, int numBits, int lineNum)
{
    /* The decimal value should be in the asymmetric range:
     *    -2^(numBits-1) <= integer < 2^(numBits-1).
     */
    int upperBound = 1 << (numBits - 1);
    int lowerBound = -1 * upperBound;
    printIntInString(intInString, numBits, lowerBound, upperBound, lineNum);
}


/* Print unsigned value in `intInString` as pseudo-binary (made up of character
 * '0's and '1's).  Prints and error if the token in the string is not a
 * valid integer or if it is not in the range 0 <= integer < 2^(numBits).
 *      @param intInString   string containing integer, e.g., "23"
 *      @param length  length of binary code needed, in bits
 *      @param lineNum line number (for error messages)
 */
void printUnsignedIntInString(char * intInString, int numBits, int lineNum)
{
    int upperBound = 1 << numBits;
    int lowerBound = 0;
    printIntInString(intInString, numBits, lowerBound, upperBound, lineNum);
}


/* Print value in `intInString` as pseudo-binary (made up of character
 * '0's and '1's).  Prints an error if the token in the string is not a
 * valid integer or if it is not in the asymmetric range given by
 *  lowerBound <= value < upperBound
 *      @param intInString   string containing integer, e.g., "23"
 *      @param numBits length of binary code needed, in bits
 *      @param lowerBound lower bound; value should be >= lowerBound
 *      @param upperBound upper bound; value should be < upperBound
 *      @param lineNum line number (for error messages)
 */
static void printIntInString(char * intInString, int numBits,
        int lowerBound, int upperBound, int lineNum)
{
    char * endPtr;

    /* Convert string to decimal (base 10) value. */
    int decimal = (int) strtol(intInString, &endPtr, 10);

    /* If the string did not contain a valid int, print an error message. */
    if ( *intInString == '\0' || *endPtr != '\0' )
    {
        printError("Line %d: trying to print %s as an int (%s).\n",
                lineNum, intInString, "not a valid integer");
        return;
    }

    /* If the decimal value is in range, print it.  Otherwise, print an
     * error message.  The value should be in the asymmetric range:
     *      lowerBound <= decimal < upperBound.
     */
    if ( decimal >= lowerBound && decimal < upperBound )
    {
        /* In range!  Print the value. */
        printInt(decimal, numBits);
    }
    else
    {
        printError("Line %d: %s is not in range %d <= %s < %d.\n",
                lineNum, intInString, lowerBound, intInString, upperBound);
    }
}


/* Print address to jump to.
 * Finds the absolute address of the label in the label table, 
 * divides it by 4 (shifts right by 2 bits) to match MIPS architecture 
 * requirements, and prints the 26-bit pseudo-binary value.
 * @param targetLabel   label being branched to
 * @param table         label table
 * @param lineNum       line number (for error messages)
 */
void printJumpTarget(char * targetLabel, LabelTableArrayList * table,
                     int lineNum)
{
   int address = findLabelAddr(table, targetLabel);
    if (address == -1) 
    {
    printError("Jump target label not found on line %d\n", lineNum);
    printInt(0, 26);
    } 
    else 
    {
    printInt(address / 4, 26);
    }

}


/* Print branch offset to branch to the target label.
 * Calculates the relative distance from the current PC (which has 
 * already been incremented by 4 in pass2.c) to the target label's address, 
 * divides the difference by 4, and prints the 16-bit pseudo-binary value.
 * @param targetLabel   label being branched to
 * @param table         label table
 * @param PC            Program Counter (already incremented by 4)
 * @param lineNum       line number (for error messages)
 */
void printBranchOffset(char * targetLabel, LabelTableArrayList * table,
                       int PC, int lineNum)
{
    int address = findLabelAddr(table, targetLabel);
    if (address == -1) 
    {
    printError("Branch target label not found on line %d\n", lineNum);
    printInt(0, 16);
    } 
    else 
    {
    int offset = (address - PC) / 4;
    printInt(offset, 16);
    }

}
