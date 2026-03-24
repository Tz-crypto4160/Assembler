/*
 * Quick and dirty test driver to test functions in printAsBinary.c
 * (not necessarily exhaustively).
 *
 * Alyce Brady
 *      - 3/5/2020: first set of tests
 *      - 3/2/2022: add range tests for signed/unsigned int in string
 */

#include "assembler.h"
int main()
{
    /* Override usual ERROR_LIMIT defined in printError.c */
    ERROR_LIMIT = 50;

    printf("About to partially test printInt:\n");
    printf("\t 5 = "); printInt(5, 3); printf(" (3 characters) \n");
    printf("\t 5 = "); printInt(5, 4); printf(" (4 characters) \n");

    printf("About to partially test printSigned/printUnsignedIntInString:\n");
    printf("\t unsigned 5 = "); printUnsignedIntInString("5", 5, 3); printf(" (5 characters) \n");
    printf("\t signed 5 = "); printSignedIntInString("5", 5, 4); printf(" (5 characters) \n");
    printf("\t unsigned 5 = "); printUnsignedIntInString("5", 3, 5); printf(" (3 characters) \n");
    printf("\t unsigned 65535 = "); printUnsignedIntInString("65535", 16, 7); printf(" (16 characters) \n");
    printf("\t signed 32767 = "); printSignedIntInString("32767", 16, 8); printf(" (16 characters) \n");
    printf("\t signed -32768 = "); printSignedIntInString("-32768", 16, 9); printf(" (16 characters) \n");

    printError("About to test invalid int sent to printUnsignedIntInString:\n");
    printError("\t q = "); printUnsignedIntInString("q", 4, 10); printError("\n");

    printError("About to test out-of-range int sent to printUnsignedIntInString:\n");
    printError("\t signed 5 in 3 characters: "); printSignedIntInString("5", 3, 6);
    printError("\t signed 65535 in 16 characters: "); printSignedIntInString("65535", 16, 11);
    printError("\t unsigned 65536 in 16 characters: "); printUnsignedIntInString("65536", 16, 12);
    printError("\t signed 32768 in 16 characters: "); printSignedIntInString("32768", 16, 13);
    printError("\t signed -32769 in 16 characters: "); printSignedIntInString("-32769", 16, 14);

    printf("About to partially test printReg:\n");
    printf("\t $zero = "); printReg("$zero", 12); printf("\n");
    printf("\t $t0 = "); printReg("$t0", 12); printf("\n");
    printf("\t $ra = "); printReg("$ra", 12); printf("\n");

    printError("About to test invalid register sent to printReg:\n");
    printError("\t $rq = "); printReg("$rq", 12); printError("\n");
}
