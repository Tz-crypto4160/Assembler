/*
 * This file contains a static global array of register names and a
 * function, g/etRegName, that looks up and returns the mnemonic name for a
 * given register number.
 *
 *    Sample client code that calls getRegName:
 *        int rNbr1, rNbr2, rNbr3;         // register numbers between 0 and 31
 *        char *rName1, *rName2, *rName3;  // will point to names, e.g., "$t0"
 *        ...                              // set register numbers
 *        rName1 = getRegName (rNbr1);
 *        rName2 = getRegName (rNbr2);
 *        rName3 = getRegName (rNbr3);
 *        printf ("add %s, %s, %s\n", rName1, rName2, rName3);
 *    If rNbr1 = 8, rNbr2 = 9, rNbr3 = 16, this will print:
 *              add $t0, $t1, $s0
 *
 * Author: Alyce Brady and Garrett Olson
 * Date:   2/10/99
 *
 *    Modified:  March 2022, AB, Make regArray static global, not static local
 *
 * 
 */

#include <string.h>
#include "names.h"
#include "same.h"

/* Create a static (persistent) array of the mnemonic names,
 *    each of which is a string (char *).  The array is a "static global"
 *    variable, meaning it is available to any functions defined in this
 *    file, but only in this file. (In this context, "static" means its
 *    scope is limited to this file).
 */
static char * regArray[] =
{
    "$zero",
    "$at",
    "$v0","$v1",
    "$a0","$a1","$a2","$a3",
    "$t0","$t1","$t2","$t3", "$t4","$t5","$t6","$t7",
    "$s0","$s1","$s2","$s3", "$s4","$s5","$s6","$s7",
    "$t8","$t9",
    "$k0","$k1",
    "$gp","$sp","$fp","$ra"
};

/* Define a named constant for the number of entries in
 * regArray.
 */
const int NUM_REGISTERS = 32;

/* This function looks up and returns the mnemonic name for a given
 * register number.
 *     Parameter: regNbr is a valid register number
 *     Pre-condition: 0 <= regNbr < 32
 *     Returns: returns a pointer to the mnemonic name associated with
 *              register number; for example: "$t0" or "$a1"
 *  The array of mnemonics is statically scoped, not local to this
 *  function, so is is safe to return a pointer to a string within it;
 *  the arrays do not disappear (their memory locations are not used for
 *  other purposes) after the function returns.
 */
char * getRegName (int regNbr)
{

    /* The precondition ensures that regNbr is a valid index into regArray,
     * i.e., that it is not out-of-bounds.
     */
    return regArray[regNbr];
}

/* This function returns the register number for the given register name.
 *  Parameter: regName  is the register name (possibly invalid)
 *  Returns:   the associated register number if regName was a valid
 *             register name; -1 otherwise
 */
int getRegNbr (char * regName)
{
    int i;

    for (i = 0; i < NUM_REGISTERS; i++) /*checking through 0~31*/
    {  

        if ( strcmp(regName, regArray[i]) == SAME ) /*if correct, the result of strcmp = SAME*/
        {  
            return i; /*return that number (i)*/
        }
    }
    /*if could not find*/
    return -1;
}

