#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	int rc = fork();
	
	if (rc < 0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) {
		execve("./progChild", argv, NULL);
	} else {
		int wc = wait(NULL);
		assert(wc >= 0);
	}
	
	return 0;
}
