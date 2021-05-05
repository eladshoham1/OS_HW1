#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "strlib.h"

int main(int argc, char *argv[]) {
	char str1[STR_LEN], str2[STR_LEN];
	int rc;
	int pfd[2];
	
	if (pipe(pfd) == -1) {
		fprintf(stderr, "pipe failed\n");
		exit(EXIT_FAILURE);
	}
	
	rc = fork();
	
	if (rc < 0) {
		fprintf(stderr, "fork failed\n");
		exit(EXIT_FAILURE);
	} else if (rc == 0) {
		if (close(pfd[1]) == -1) {
			fprintf(stderr, "close failed\n");
			exit(EXIT_FAILURE);
		}
		
		if (pfd[0] != STDOUT_FILENO) {
			if (dup2(pfd[0], STDOUT_FILENO) == -1) {
				fprintf(stderr, "dup2 failed\n");
				exit(EXIT_FAILURE);
			}
			
			close(pfd[0]);
		}

		char *args[] = {"xorstr", NULL };
		execve(args[0], args, NULL);
	} else {
		printf("Please, Enter string number 1: ");
		mygets(str1, STR_LEN);
		
		printf("Please, Enter string number 2: ");
		mygets(str2, STR_LEN);
		
		close(pfd[0]);
		
		write(pfd[1], str1, strlen(str1));
		write(pfd[1], str2, strlen(str2));
		
		close(pfd[1]);
		wait(NULL);
	}

	return EXIT_SUCCESS;
}
