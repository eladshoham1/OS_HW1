#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "strlib.h"

int main(int argc, char *argv[]) {
	int rc;
	int pfd[2];
	
	if (pipe(pfd) == -1) {
		fprintf(stderr, "pipe failed\n");
		exit(EXIT_FAILURE);
	}
	
	rc = fork();
	
	if (rc < 0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) {
		
	} else {
		if (close(pfd[0]) == -1)
			fprintf(stderr, "close failed\n");
		if (close(pfd[1]) == -1)
			fprintf(stderr, "close failed\n");
		if (wait(NULL)== -1)
			fprintf(stderr, "wait failed\n");
		exit(EXIT_SUCCESS);
	}
	
	return 0;
}
