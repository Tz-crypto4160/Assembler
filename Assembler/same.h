/*
 * This file contains the declaration for the global named constant SAME,
 * which is defined in same.c.
 * The purpose of this named constant is to make for more readable calls
 * to the standard strcmp function found in string.h.  Proper usage is,
 * for example,
 *      if (strcmp (str1, str2) == SAME)
 * Since C programmers are trained to read 0 as "false", use of SAME leads
 * to more readable (less likely to be misinterpreted) code than the default
 * equivalent code:
 *      if (strcmp (str1, str2) == 0)
 */

#ifndef _SAME_H
#define _SAME_H

extern const int SAME;		/* useful for making strcmp readable */
                                /* e.g., if (strcmp (str1, str2) == SAME) */

#endif
