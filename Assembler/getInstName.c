
#include "assembler.h"

/* Get instruction name.
 * This function skips any leading whitespace or label, and strips
 * comments.  It then separates the instruction name (assuming there is
 * one) from the rest of the line, "returning" pointers to those two
 * strings in the two "pass-by-reference" parameters (which should actually
 * be addresses of the values to be returned).
 *    @param input        the line read in
 *    @param instrName    address where pointer to instruction name
 *                          should be placed; NULL if the line was
 *                          empty, contained only a comment, or
 *                          contained only a label
 *    @param restOfLine   address where pointer to rest of line should
 *                          be placed
 * Author: Alyce Brady
 * Date:   Last modified March 2020 (abstracted out from pass2.c)
 *
 */
void getInstName(char * input, char ** instrName, char **restOfLine)
{
    char * tokBegin, * tokEnd;     /* used to step thru input */

    /* If the line starts with a comment, move on to next line.  */
    if ( *input == '#' )
    {
        *instrName = NULL;
        return;
    }

    /* If there's a comment later in the line, strip it off
     *  (replace the '#' with a null byte).
     */
    (void) strtok (input, "#");

    /* Read the first token, skipping any leading whitespace. */
    tokBegin = input;
    getToken (&tokBegin, &tokEnd);
        /* tokBegin now points to 1st non-whitespace character
         * in the token and tokEnd points to 1st punctuation mark
         * or whitespace after the end of the token.
         */

    /* Skip label, if any */
    if ( *(tokEnd) == ':' )
    {
        /* Line has a label!  Get new token! */
        tokBegin = tokEnd + 1;
        getToken (&tokBegin, &tokEnd);
    }

    /* If empty line or line containing only a label, get next line */
    if ( *tokBegin == '\0' )
    {
        *instrName = NULL;
        return;
    }

    /* We have a valid token; turn it into a string and set
     * tokBegin to point to the character after the end.
     */
    *tokEnd = '\0';
    *instrName = tokBegin;
    *restOfLine = tokEnd + 1;
}
