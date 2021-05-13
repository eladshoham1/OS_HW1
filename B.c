#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "strlib.h"

/* Version B: passing args to child through pipe */
int main(int argc, char *argv[]) {
	int rc;
	int parentToChild[2], childToParent[2];
	
	if (pipe(parentToChild) == -1 || pipe(childToParent) == -1) {
		fprintf(stderr, "pipe failed\n");
		exit(EXIT_FAILURE);
	}
	
	rc = fork();
	
	if (rc < 0) {
		fprintf(stderr, "fork failed\n");
		exit(EXIT_FAILURE);
	} else if (rc == 0) {
		dup2(parentToChild[0], fileno(stdin));
		close(childToParent[0]);
		close(parentToChild[0]);
	
		dup2(childToParent[1], fileno(stdout));
		close(parentToChild[1]);
		close(childToParent[1]);
	
	
		/*if (close(pfd[1]) == -1) {
			fprintf(stderr, "close failed\n");
			exit(EXIT_FAILURE);
		}


		if (pfd[0] != STDIN_FILENO) {
			if (dup2(pfd[0], STDIN_FILENO) == -1) {
				fprintf(stderr, "dup2 failed\n");
				exit(EXIT_FAILURE);
			}
			
			close(pfd[0]);
		}*/

		char *args[] = {"xorstr", NULL };
		execve(args[0], args, NULL);
	} else {
		while (!feof(stdin)) {
			char str1[STR_LEN + 1], str2[STR_LEN + 1], res[STR_LEN + 1];
			close(childToParent[1]);
			close(parentToChild[0]);
			
			printf("Please, Enter string number 1: ");
			mygets(str1, STR_LEN);
			
			printf("Please, Enter string number 2: ");
			mygets(str2, STR_LEN);
			
			fflush(stdin);
			strcat(str1, NEW_LINE);
			strcat(str2, NEW_LINE);
			
			write(parentToChild[1], str1, strlen(str1));
			write(parentToChild[1], str2, strlen(str2));
			
			read(childToParent[0], res, sizeof(res));
			puts(res);
			memset(res, 0, sizeof(res));
		}
	}

	return EXIT_SUCCESS;
}
