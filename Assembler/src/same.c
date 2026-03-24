/*
 * This file merely defines the global named constant SAME.
 * The purpose of this named constant is to make for more readable calls
 * to the standard strcmp function found in string.h.  Proper usage is,
 * for example,
 *      if (strcmp (str1, str2) == SAME)
 * Since C programmers are trained to read 0 as "false", use of SAME leads
 * to more readable (less likely to be misinterpreted) code than the default
 * equivalent code:
 *      if (strcmp (str1, str2) == 0)
 *
 * Author:  Alyce Brady
 *
 * Creation Date:  21 May 2019
 *
 */

/* include files go here */
#include "same.h"

const int SAME = 0;             /* useful for making strcmp readable */
                                /* e.g., if (strcmp (str1, str2) == SAME) */

