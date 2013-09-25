/*
 *  Project 1 - main.c
 *
 *  Matthew Brauner
 *  Professor Sommers
 *  CS 301
 *  September 25, 2013
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "list.h"

void usage(char *program) {
    fprintf(stderr, "usage: %s [<datafile>]\n", program);
    exit(1);
}


int main(int argc, char **argv) {
	struct rusage usg;
	struct timeval user, system;

    FILE *datafile = NULL;

    /* find out how we got invoked and deal with it */
    switch (argc) {
        case 1:
            /* only one program argument (the program name) */ 
            /* just equate stdin with our datafile */
            datafile = stdin;
            break;

        case 2:
            /* two arguments: program name and input file */
            /* open the file, assign to datafile */
            datafile = fopen(argv[1], "r");
            if (datafile == NULL) {
                printf("Unable to open file %s: %s\n", argv[1], strerror(errno));
                exit(-1);
            }
            break;

        default:
            /* more than two arguments?  throw hands up in resignation */
            usage(argv[0]);
    }

	char buffer[256];
	struct node *head = NULL;
	struct node **phead = &head;

	// read each line
	while (fgets(buffer, 256, datafile) != NULL) {
		const char s[2]= " ";
		char *token;
		token = strtok(buffer, s);

		// tokenize each line and check each token for integers
		while (token != NULL) {

			// ignore comments and newline characters
			if (strncmp(token, "#", 1)==0 || strcmp(token, "\n")==0) {
				break;
			}

			// check first character for either a digit or negative sign
			if (( token[0]>=(int)'0' && token[0]<=(int)'9' ) || token[0]==(int)'-') {


				// check remaining characters for digits
				int i=1;
				int check=1;
				int tlen=strlen(token);

				for (; i < tlen ; i++) {
					if (token[i]<(int)'0' || token[i]>(int)'9') {
						check=0;
						break;
					}
				}

				// if check is still equal to 1, we have an integer so we can add it to the linked list
				if (check==1) {
					const int t = atoi(token);
					list_insert(t,phead);
				}
			}

			token = strtok(NULL,s);
		}
	}

	printf("*** List Contents Begin ***\n");
	list_print(head);
	printf("*** List Contents End ***\n");

	int rv = getrusage(RUSAGE_SELF, &usg);
	system = usg.ru_stime;
	user = usg.ru_utime;

	if (rv == 0) {
		printf("User time: %ld.%06ld\n", user.tv_sec, user.tv_usec);
		printf("System time: %ld.%06ld\n", system.tv_sec, system.tv_usec);
	} else {
		printf("Time measurement error\n");
	}

	list_clear(head);
	fclose(datafile);
	return 0;
}

