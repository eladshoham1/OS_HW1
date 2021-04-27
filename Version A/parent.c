#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/wait.h>
#include "../functions.h"

int main(int argc, char* argv[]) {
	char str1[STR_LEN], str2[STR_LEN];
	int rc = fork();
	
	if (rc < 0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) {
		printf("Please, Enter string number 1: ");
		fgets(str1, STR_LEN, stdin);
		printf("Please, Enter string number 2: ");
		fgets(str2, STR_LEN, stdin);
		execve("./progChild", argv, NULL);
	} else {
		int wc = wait(NULL); // pointer to wait for getting response for the child logic
		assert(wc >= 0);
	}
	
	return 0;
}
