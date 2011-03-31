/*
 * Minimalistic shell
 * (c) 2011 Jeremy Baumont
 *
 *
 */
#include <stdio.h>
#include <string.h>

#include "parse.h"

int
main(int argc, char *argv[], char *envp[]) {
    	
    	char tmp[CMD_LINE_SIZE];
    	char *prompt = "jshell>";
    	int cargc = 0;
    	char *cargv[CMD_LINE_SIZE];
    	char *cenvp[CMD_LINE_SIZE];
    	char in[FILENAME_SIZE];
    	char out[FILENAME_SIZE];
    	int am = WRONLY;
    	int c;
    	
    	memset(tmp, '\0', sizeof(tmp));
    	memset(in, '\0', sizeof(in));
    	memset(out, '\0', sizeof(out));
    	memset(cargv, '\0', sizeof(cargv));
    	memset(cenvp, '\0', sizeof(cenvp));
	printf("\n%s", prompt);
    	while(c != EOF) {
		c = getchar();
		switch(c) {
	    		case '\n': /* parse and execute. */
				parse(tmp, &cargc, cargv, 
					cenvp, in, out, &am);
				execute(&cargc, cargv, cenvp, in, out, &am);
				memset(tmp, 0, sizeof(tmp));
				memset(cargv, 0, sizeof(cargv));
				memset(cenvp, 0, sizeof(cenvp));
    				memset(in, '\0', sizeof(in));
    				memset(out, '\0', sizeof(out));
				am = WRONLY;
				cargc = 0;
				printf("\n%s", prompt);
				break;
	    		default: 
				strncat(tmp, (const char*) &c, 1);
				break;
		}
    }	
	
    /* some processing before terminating. */
    return 0;
}
