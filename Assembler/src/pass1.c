/**
 * LabelTableArrayList pass1 (FILE * fp)
 *      @param  fp  pointer to an open file (stdin or other file pointer)
 *                  from which to read lines of assembly source code
 *      @return a newly-created table containing labels found in the
 *              input file, each with the address of the instruction
 *              containing it (assuming the first line of input
 *              corresponds to address 0)
 *
 * This function reads the lines in an assembly source file and looks
 * for labeled statements.  It builds a table of labels and addresses.
 * It returns a copy of the table it created.  If an error occurs, the
 * function prints an error message and returns the table as it exists
 * at that point (possibly empty).
 *
 * Author: Alyce Brady
 * Date:   2/16/99
 *
 * Modified by:  Alyce Brady, 6/10/2014
 *      Take open file pointer as parameter, rather than filename.
 *
 */

#include "assembler.h"

/* Declare function used internally within this file. */
char * getLabel(char * input);

LabelTableArrayList pass1 (FILE * fp)
  /* returns a copy of the label table that was constructed */
{
    LabelTableArrayList table;     /* the table of labels & addresses */
    int    PC = 0;                 /* the program counter */
    char   inst[BUFSIZ];           /* will hold instruction; BUFSIZ
                                      is max size of I/O buffer
                                      (defined in stdio.h) */
    char * label;                  /* label found in an instruction */

    /* create a small label table to begin with */
    tableInit (&table);
    if ( tableResize (&table, 10) == 0)
    {
        /* error message already printed */
        return table;
    }

    /* Continuously read next line of input until EOF is encountered.
     * Check each line to see if it has a label; if it does, add it
     * to the label table.
     */
    for (PC = 0; fgets (inst, BUFSIZ, fp); PC += 4)
    {
        /* Get the label, if there is one on this line. */
        label = getLabel(inst);

        /* Was a label found? */
        if ( label != NULL )
        {
            /* Label found: add to table.
             * (If there's an error, addLabel should print the error message.)
             */
            addLabel (&table, label, PC);
        }
    }

    /* EOF, but don't close the file here. */
    return table;
}

/* Get label.
 * This function skips any leading whitespace and looks to see if there
 * is a label in the instruction.  If there is one, it replaces the colon
 * separator with a null byte and returns the address of the beginning
 * of the label.  If there is no label, the function returns NULL.
 *    @param input  the line read in
 *    @return       a label, if the line starts with one, or NULL otherwise
 */
char * getLabel(char * input)
{
    char * tokBegin, * tokEnd;     /* used to step thru input */

    /* If the line starts with a comment, move on to next line.  */
    if ( *input == '#' )
        return NULL;

    /* If there's a comment later in the line, strip it off
     *  (replace the '#' with a null byte).
     */
    (void) strtok (input, "#");

    /* Read the first token, skipping any leading whitespace. */
    tokBegin = input;
    getToken (&tokBegin, &tokEnd);
        /* tokBegin now points to 1st non-whitespace character in the token
         * and tokEnd points to 1st punctuation mark or whitespace after
         * the end of the token.
         */

    /* Check each line to see if it has a label; if it does, process it. */
    if ( *(tokEnd) == ':' )
    {
        /* Line contains a label! */
        *tokEnd = '\0';      /* truncate everything after label */
        return tokBegin;
    }

    /* This line does not contain a label. */
    return NULL;
}
