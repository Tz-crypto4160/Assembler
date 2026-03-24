/**
 * This program converts a file with the "wrong" kind of newline to a
 * file with the "right" kind of newline for the machine you are running
 * on.  If the lines end in \r\n and your machine expects \n, this program
 * will write lines ending in \n to stdout.  I believe it will also do the
 * reverse, although I haven't tested it on a Windows machine.
 *
 * The input can come from stdin or from a file specified on the command
 * line.
 */

/* include files go here */
#include "assembler.h"

int main (int argc, char *argv[])
{
    FILE * fptr;               /* file pointer */
    char   buffer[BUFSIZ];     /* place to store line that is read in */
    int    length;             /* length of line read in */

    /* Process command-line arguments (if any) -- input file name
     *    and/or debugging indicator (1 = on; 0 = off).
     */
    fptr = process_arguments(argc, argv);
    if ( fptr == NULL )
    {
        return 1;   /* Fatal error when processing arguments */
    }

    /* Can turn debugging on or off here (debug_on() or debug_off())
     * if not specified on the command line.
     */

    /* Continuously read next line of input until EOF is encountered.
     * Each line should contain an ASCII version of a valid MIPS machine
     * language instruction, represented as 32 character '0's and '1's
     * followed by a newline, rather an actual 32-bit binary MIPS
     * machine language instruction.
     */
    while (fgets (buffer, BUFSIZ, fptr))   /* fgets returns NULL if EOF */
    {
        /* If the last character in the string is a newline, "remove" it
         * by replacing it with a null byte. (On Windows, the newline might
         * be preceded by a separate carriage return.)
         */
        length = strlen(buffer);
        if (buffer[length - 1] == '\n')
            buffer[--length] = '\0';      /* remove; pre-decrement length */
        if (buffer[length - 1] == '\r')
            buffer[--length] = '\0';      /* remove; pre-decrement length */

        /* If debugging is turned on, echo the input line. */
        printf ("%s\n", buffer);
    }

    /* End-of-file encountered; close the file. */
    fclose (fptr);
    return 0;
}
