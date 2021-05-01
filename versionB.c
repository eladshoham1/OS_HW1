#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "functions.h"

int main(int argc, char *argv[]) {
	int res = 0, rc;
	int pipefd[2];
	
	do {
		if (pipe(pipefd) == -1) {
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		
		rc = fork();
		
		if (rc < 0) {
			fprintf(stderr, "fork failed\n");
			exit(1);
		} else if (rc == 0) {
			close(pipefd[1]);
			char buf; // check only
			
			while (read(pipefd[0], &buf, 1) > 0)
				write(STDOUT_FILENO, &buf, 1);
				
			write(STDOUT_FILENO, "\n", 1);
			close(pipefd[0]);
			_exit(EXIT_SUCCESS);
		} else {
			close(pipefd[0]);
			write(pipefd[1], argv[1], strlen(argv[1]));
			write(pipefd[1], argv[2], strlen(argv[2]));
			close(pipefd[1]);
			wait(&res);
			res = WEXITSTATUS(res);
			printf("xor result: %d\n", res);
			exit(EXIT_SUCCESS);
		}
	} while (1);
	
	return res;
}
