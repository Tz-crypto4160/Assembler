/* 
 * This is the main driver for the MIPS Assembler.
 *
 *  This is the main driver program for the MIPS Assembler.
 *
 *  The program implements a two-pass assembler. It first calls pass1 
 *  to construct a table of instruction labels and addresses. Then, 
 *  it rewinds the file and calls pass2 to translate the MIPS assembly 
 *  instructions into 32-bit pseudo-binary machine code.
 *
 *      For example, the following three lines of code would result in a
 *      table with one entry, indicating that label A_LABEL is at address 4.
 *                add $t1, $t1, $t1   # This instruction is at address 0
 *      A_LABEL:  slt $t0, $t1, $t2   # This instruction is at address 4
 *                bne $t0, $zero, A_LABEL  # This instr. is at address 8
 *
 * USAGE:
 *          name filename [ 0|1 ]
 *      where "name" is the name of the executable, "filename" is a
 *      file containing the input to read, and the optional "0" or "1"
 *      specifies that debugging should be turned off or on, respectively,
 *      regardless of any calls to debug_on, debug_off, or debug_restore in
 *      the program.  If both arguments are present, they may appear in
 *      either order.  If no debugging choice is provided, the program
 *      prints debugging messages, or not, depending on indications in the
 *      code.
 *
 * INPUT:
 *      This program expects the input to consist of lines of MIPS
 *      instructions, each of which may (or may not) contain a label at the
 *      beginning of the line.  The input should have one MIPS instruction
 *      on each line.  Labels should appear as the first token in the line,
 *      followed immediately by a colon.  Labels may also appear elsewhere
 *      in an instruction, but those labels are ignored by this program.
 *
 * OUTPUT:
 *      The program prints the 32-bit pseudo-binary machine language 
 *      instructions corresponding to the MIPS assembly input to standard 
 *      output. If debugging has been turned on, it also prints the 
 *      contents of the label table and other debugging information.
 *
 * ERROR CONDITIONS:
 *    - It is an error to call this function without a filename.
 *    - It is an error for the input to contain multiple instructions with
 *      the same label at the beginning of the line.
 *
 * Author: Alyce Brady
 * Date: 2/18/99
 *
 * Modified by:  Alyce Brady, 6/10/2014
 *      Allow filename to be passed as a parameter.
 * Modified by:  Alyce Brady, 5/25/2015
 *      Support use of printErr and printDebug functions.
 *      Improve function documentation.
 * Modified by:  Alyce Brady, 6/2/2019
 *      Improve function documentation.
 * Modified by:  Alyce Brady, 11/19/2023
 *      Require filename (no longer optional), since it doesn't make sense
 *      for a two-pass assembler to get input from stdin.  (And it doesn't
 *      add useful functionality for the initial test for pass1, either.)
 *      Thanks to Jordan Doyle for pointing this out.
 * Modified by: Taiki Sawamata, 03/10/2026
 *      Updated documentation to reflect the full assembler behavior.
 *      Added file rewind and call to pass2 to complete the 
 *      two-pass assembly process.
 */

#include "assembler.h"

int main (int argc, char * argv[])
{
    FILE * fptr;               /* file pointer */
    LabelTableArrayList table;

    /* Process command-line arguments (if any) -- input file name
     *    and/or debugging indicator (1 = on; 0 = off).
     */
    fptr = process_arguments(argc, argv);
    if ( fptr == NULL )
    {
        return 1;   /* Fatal error when processing arguments */
    }

    /* Provide warning if user did not specify input file on command line. */
    if ( fptr == stdin )
    {
        printf("%s", "Error: No input file provided.\n");
        return 2;
    }

    /* Call pass1 to generate the label table. */
    table = pass1 (fptr);

    /* Print the label table if debugging is turned on. */
    if ( debug_is_on() )
        printLabels (&table);

    /*rewind the pointer to be back at the beginning*/
     rewind(fptr);
    /*call pass2, then execute assembling*/
     pass2(fptr, &table);

    (void) fclose(fptr);
    return 0;
}
