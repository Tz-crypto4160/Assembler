/**
 * void pass2 (FILE * fp, LabelTableArrayList * table)
 *      @param  fp  pointer to an open file (stdin or other file pointer)
 *                  from which to read lines of assembly source code
 *      @param  table  a pointer to an existing Label Table
 *
 * DESCRIPTION :
 *      This file contains the functions that execute the second pass of a 
 *      two-pass MIPS assembler. It parses each instruction to determine its 
 *      format (R, I, or J) and uses the corresponding opcode, funct code, and 
 *      registers to print the instruction as a 32-bit pseudo-binary string.
 *
 *
 * Author: <author> Taiki Sawamata
 * Date:   <date> 03/10/2026
 *
 * Modified by: Taiki Sawamata
 *      Implemented processR and processIorJ to correctly parse arguments 
 *      and print pseudo-binary output.
 *
 */

#include "assembler.h"

void pass2 (FILE * fp, LabelTableArrayList * table)
{
    int    lineNum;            /* line number */
    int    PC = 0;             /* program counter */
    char   inst[BUFSIZ];       /* will hold instruction; BUFSIZ is max size
                                    of I/O buffer (defined in stdio.h) */
    char * instrName;          /* instruction name (e.g., "add") */
    char * restOfInstruction;  /* rest of instruction (e.g., "$t0, $t1, $t2") */

    /* Continuously read next line of input until EOF is encountered.
     */
    for (lineNum = 1; fgets (inst, BUFSIZ, fp); lineNum++)
    {
        PC += 4;

        /* Separate the instruction name from the rest of the statement.
         * If the line does not have an instruction, move on to next line.
         */
        getInstName(inst, &instrName, &restOfInstruction);
        if ( instrName == NULL )
            continue; /* Go to top of loop to read next line of input. */

        /*printDebug ("First non-label token is: %s\n", instrName);*/

        /* Determine whether this is an R-format, I-format, or J-format
         * instruction based on the opcode.  If it is an R-format
         * instruction, get the funct code also.  Then process the
         * instruction.
         */
        int opcode = getOpCode(instrName);
        /*printDebug("%s instruction has opcode %d.\n", instrName, opcode);*/
        if ( opcode == 0 )
        {
            int functCode = getFunctCode(instrName);
            /*printDebug("%s instruction has funct code %d.\n",
                    instrName, functCode);*/
            if ( functCode == -1 )
            {
                /* Print error message - this is not a valid instruction!  */
                printError("Invalid instruction %s on line %d.\n", instrName,
                        lineNum);
                continue; /* Go to top of loop to read next line of input. */
            }

            processR(lineNum, functCode, restOfInstruction);
        }
        else
        {
            processIorJ(lineNum, table, opcode, restOfInstruction, PC);
        }
    }

    return;
}

/* * Processes and prints an R-format instruction in pseudo-binary.
 * @param lineNum          current line number in the source file
 * @param functCode        the 6-bit funct code for this instruction
 * @param restOfInstruction a string containing the operands
 * * Uses getNTokens to parse the operands, then calls print functions 
 * to output the opcode, registers, shift amount, and funct code.
 * Handles special cases like shifts (sll, srl) and jump register (jr).
 */

void processR(int lineNum, int functCode, char * restOfInstruction)
{
    char * arguments[3];      /* registers or values after name; max of 3 */
    int numOperands;

    /* Get arguments from restOfInstruction using getNTokens.  Depending on
     * the instruction, getNTokens could fill 1, 2, or 3 arguments in the
     * arguments array.  For example, for instruction "add $t0, $t1, $t2",
     * getNTokens would fill the arguments array with the strings "$t0",
     * "$t1", and "$t2", in that order.
     * R-Format instructions always have either 1 or 3 arguments.
     */
    if ( functCode == 8 )       /* jr instruction has only 1 operand. */
        numOperands = 1;
    else
        numOperands = 3;        /* all other R instructions have 3 operands */
    if ( ! getNTokens(restOfInstruction, numOperands, arguments) )
    {
        printError("Error on line %d: %s\n", lineNum, arguments[0]);
        return;
    }


    /* Print machine code version of instruction and arguments in correct
     * order.  First handle the exceptions (unusual formats), and then
     * the common format for add, sub, and, etc.
     */
    if ( functCode == 8 )       /* Handle jr instruction */
    {
        /*printDebug("jr \"%s\"\n", arguments[0]);*/

        printInt(0, 6);                 /* opcode = 0 */
        printReg(arguments[0], lineNum);/* rs */
        printInt(0, 5);                 /* rt = 0 */
        printInt(0, 5);                 /* rd = 0 */
        printInt(0, 5);                 /* shamt = 0 */
        printInt(functCode, 6);         /* funct */
        printf("\n");

    }
    
    else if ( functCode == 0 || functCode == 2 || functCode == 3 ) /* sll, srl, sra (shift) */
    {
        printInt(0, 6);                 /* opcode = 0 */
        printInt(0, 5);                 /* rs = 0 */
        printReg(arguments[1], lineNum);/* rt */
        printReg(arguments[0], lineNum);/* rd */
        printUnsignedIntInString(arguments[2], 5, lineNum); /* shamt */
        printInt(functCode, 6);         /* funct */
        printf("\n");
    }
    else                        /* Handle common format for add, etc. */
    {
        /*printDebug("funct %d \"%s\", \"%s\", and \"%s\"\n", functCode,*/
        printInt(0, 6);                 /* opcode = 0 */
        printReg(arguments[1], lineNum);/* rs */
        printReg(arguments[2], lineNum);/* rt */
        printReg(arguments[0], lineNum);/* rd */
        printInt(0, 5);                 /* shamt = 0 */
        printInt(functCode, 6);         /* funct */
        printf("\n");
    }

}

/* * Processes and prints an I-format or J-format instruction in pseudo-binary.
 * @param lineNum          current line number in the source file
 * @param table            pointer to the populated label table
 * @param opcode           the 6-bit opcode for this instruction
 * @param restOfInstruction a string containing the operands
 * @param PC               the current Program Counter address
 * * Uses getNTokens to parse the operands, then calls print functions 
 * to output the opcode, registers, and immediate value or target address.
 * Handles special cases like branches (beq, bne) and jumps (j, jal).
 */
void processIorJ(int lineNum, LabelTableArrayList * table,
                 int opcode, char * restOfInstruction, int PC)
{
    char * arguments[3];      /* registers or values after name; max of 3 */
    int numOperands;

    /* J-format (j, jal) */
if ( opcode == 2 || opcode == 3 )
    numOperands = 1;
/* lui */
else if ( opcode == 15 )
    numOperands = 2;
/* other I-format */
else
    numOperands = 3;

if ( ! getNTokens(restOfInstruction, numOperands, arguments) )
{
    printError("Error on line %d: %s\n", lineNum, arguments[0]);
    return;
}

/* J-format (j, jal) */
if ( opcode == 2 || opcode == 3 )
{
    printInt(opcode, 6);
    printJumpTarget(arguments[0], table, lineNum);
    printf("\n");
}
/* Branch instructions (beq, bne) */
else if ( opcode == 4 || opcode == 5 )
{
    printInt(opcode, 6);
    printReg(arguments[0], lineNum); /* rs */
    printReg(arguments[1], lineNum); /* rt */
    printBranchOffset(arguments[2], table, PC, lineNum);
    printf("\n");
}
/* Load / Store (lw, sw, lb, sb, etc.) */
else if ( opcode == 35 || opcode == 43 || opcode == 32 || opcode == 40 || opcode == 36 )
{
    printInt(opcode, 6);
    printReg(arguments[2], lineNum); /* rs */
    printReg(arguments[0], lineNum); /* rt */
    printSignedIntInString(arguments[1], 16, lineNum); /* imm */
    printf("\n");
}
/* lui (Load Upper Immediate) */
else if ( opcode == 15 )
{
    printInt(opcode, 6);
    printInt(0, 5);                  /* rs = 0 */
    printReg(arguments[0], lineNum); /* rt */
    printUnsignedIntInString(arguments[1], 16, lineNum); /* imm */
    printf("\n");
}
/* Standard I-format (addi, andi, ori, slti, etc.) */
else
{
    printInt(opcode, 6);
    printReg(arguments[1], lineNum); /* rs */
    printReg(arguments[0], lineNum); /* rt */
    
    /* andi(12), ori(13), xori(14) are zero-extended (unsigned) */
    if ( opcode == 12 || opcode == 13 || opcode == 14 ) 
    {
        printUnsignedIntInString(arguments[2], 16, lineNum);
    } 
    else 
    {
        printSignedIntInString(arguments[2], 16, lineNum);
    }
    printf("\n");
}

}
