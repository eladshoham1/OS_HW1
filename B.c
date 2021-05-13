#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "strlib.h"

/* Version B: passing args to child through pipe */
int main(int argc, char *argv[]) {
	int parentToChild[2], childToParent[2], rc;
	
	if (pipe(parentToChild) == -1 || pipe(childToParent) == -1) {
		fprintf(stderr, "pipe failed\n");
		exit(EXIT_FAILURE);
	}
	
	rc = fork();
	
	if (rc < 0) {
		fprintf(stderr, "fork failed\n");
		exit(EXIT_FAILURE);
	} else if (rc == 0) {
		if (parentToChild[0] != fileno(stdin)) {
			if (dup2(parentToChild[0], fileno(stdin)) == -1) {
				fprintf(stderr, "Parent to child 0 dup2 failed\n");
				exit(EXIT_FAILURE);
			}
		}
		
		if (close(childToParent[0]) == -1) {
			fprintf(stderr, "Child to parent 0 close failed\n");
			exit(EXIT_FAILURE);
		}
		
		if (close(parentToChild[0]) == -1) {
			fprintf(stderr, "Parent to child 0 close failed\n");
			exit(EXIT_FAILURE);
		}
	
		if (childToParent[1] != fileno(stdout)) {
			if (dup2(childToParent[1], fileno(stdout)) == -1) {
				fprintf(stderr, "dup2 failed\n");
				exit(EXIT_FAILURE);
			}
		}
		
		if (close(parentToChild[1]) == -1) {
			fprintf(stderr, "Parent to child 1 close failed\n");
			exit(EXIT_FAILURE);
		}
		
		if (close(childToParent[1]) == -1) {
			fprintf(stderr, "Child to parent 1 close failed\n");
			exit(EXIT_FAILURE);
		}

		char *args[] = {"xorstr", NULL };
		execve(args[0], args, NULL);
	} else {
		if (close(childToParent[1]) == -1) {
			fprintf(stderr, "Child to parent 1 close failed\n");
			exit(EXIT_FAILURE);
		}
	
		if (close(parentToChild[0]) == -1) {
			fprintf(stderr, "Parent to child 0 close failed\n");
			exit(EXIT_FAILURE);
		}
		
		while (!feof(stdin)) {
			char str1[STR_LEN + 1], str2[STR_LEN + 1], res[STR_LEN + 1];

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
			printf("%s", res);
			
			memset(res, 0, sizeof(res));
		}
	}

	return EXIT_SUCCESS;
}
