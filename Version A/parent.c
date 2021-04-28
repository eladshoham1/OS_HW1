#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../functions.h"

int main() {
	char str1[STR_LEN], str2[STR_LEN];
	int res, rc = fork();
	
	if (rc < 0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) {
		printf("Please, Enter string number 1: ");
		fgets(str1, STR_LEN, stdin);
		
		printf("Please, Enter string number 2: ");
		fgets(str2, STR_LEN, stdin);
		
		char *args[] = { str1, str2, NULL };
		execve("./progChild", args, NULL);
	} else {
		wait(&res);
		printf("xor result: %d\n", WEXITSTATUS(res));
	}
	
	return 0;
}
