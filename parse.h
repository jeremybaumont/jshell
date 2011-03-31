/*
 * Command line parsing of the minimalistic shell
 * (c) 2011 Jeremy Baumont
 *
 * 1) Scan through the line for redirection symbols, keeping track of
 * the input and output file names if they exist. Check for errors such
 * as multiple redirection or missing file names (i.e. a redirection
 * token that is not followed by a file name) at this point.
 *
 * 2) Remove all traces of redirection from the command line (i.e.
 * replace the relevant characters with blanks).
 *
 * 3) Split the line in to words. The first word will be the command,
 * and each subsequent word will be an argument to the command.
 *
 *
 *
 */
#ifndef PARSE_H
#define PARSE_H

#include "limits.h"

/*
 * parse -- Parses the command line
 *
 * 1) Scan through the line for redirection symbols, keeping track of
 * the input and output file names if they exist. Check for errors such
 * as multiple redirection or missing file names (i.e. a redirection
 * token that is not followed by a file name) at this point.
 *
 * 2) Remove all traces of redirection from the command line (i.e.
 * replace the relevant characters with blanks).
 *
 * 3) Split the line in to words. The first word will be the command,
 * and each subsequent word will be an argument to the command.
 *
 *
 *
 */
extern void parse(char buf[], int *cargc,char *cargv[], char *cenvp[], char *in, char *out, int *am);

/*
 * execute -- Execute program of parsed command line
 *
 */
extern void execute(int *cargc, char *cargv[], char *cenvp[], char *in, char *out, int *am);

#endif
