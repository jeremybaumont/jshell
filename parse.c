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
 */
#include <stdio.h>
#include <string.h>
#include "parse.h"

char *
__strsep (char **stringp, const char *delim)
{
  char *begin, *end;

  begin = *stringp;
  if (begin == NULL)
    return NULL;

  /* A frequent case is when the delimiter string contains only one
     character.  Here we don't need to call the expensive `strpbrk'
     function and instead work using `strchr'.  */
  if (delim[0] == '\0' || delim[1] == '\0')
    {
      char ch = delim[0];

      if (ch == '\0')
    end = NULL;
      else
    {
      if (*begin == ch)
        end = begin;
      else if (*begin == '\0')
        end = NULL;
      else
        end = strchr (begin + 1, ch);
    }
    }
  else
    /* Find the end of the token.  */
    end = strpbrk (begin, delim);

  if (end)
    {
      /* Terminate the token and set *STRINGP past NUL character.  */
      *end++ = '\0';
      *stringp = end;
    }
  else
    /* No more delimiters; this is the last token.  */
    *stringp = NULL;

  return begin;
}


void parse (char buf[], int *cargc, char *cargv[], char *cenvp[], 
		char *in, char *out, int *am) {
	char *delimiters = " \r\n";
	char *indelimiter = "<";
	char *outdelimiter = ">";
	char *token;
	char *subtoken;
	char *running;

	running = buf;
	*cargc = 0;

	while ((token = __strsep(&running, delimiters))) {
		if((subtoken = strpbrk(token, indelimiter))){ 
			strcpy(in, subtoken+1);
			continue;
		}

		if((subtoken = strpbrk(token, outdelimiter))) { 	
			if (*(subtoken + 1) == '>') {
				subtoken++;
			}
			strcpy(out, subtoken+1);
			continue;
		}
		if (*token == '<'){
			strcpy(in,__strsep(&running, delimiters));
			continue;
		}

		if (*token == '>'){
			strcpy(out,__strsep(&running, delimiters));
			*am = WRONLY;
			continue;
		}
		if (strcmp(token, ">>") == 0){
			strcpy(out,__strsep(&running, delimiters));
			*am = APPEND;
			continue;
		}

		cargv[*cargc] = token;
		*cargc = *cargc + 1;
	}
}


void execute( int *cargc, char *cargv[], char *cenvp[], char *in, char *out, int *am) {
	int i = 0;
	printf("number of arguments: %d\n", *cargc);
	printf("arguments: ");
	for (i = 0; i <*cargc; i++) {
		printf("%s ", cargv[i]);
	}	
	if(in != NULL) {
	    printf("\ninput file: %s \n", in);
	}
	if(out != NULL) {
	    printf("output file: %s, with access mode: %d \n", out, *am);
	}
}

