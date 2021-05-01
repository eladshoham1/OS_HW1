#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "functions.h"

int main(int argc, char *argv[]) {
	char str1[STR_LEN], str2[STR_LEN];
	int res = 0, rc;
	
	do {
		rc = fork();
		
		if (rc < 0) {
			fprintf(stderr, "fork failed\n");
			exit(1);
		} else if (rc == 0) {
			printf("Please, Enter string number 1: ");
			fgets(str1, STR_LEN, stdin);
			
			printf("Please, Enter string number 2: ");
			fgets(str2, STR_LEN, stdin);
			
			char *args[] = {"./child", str1, str2, NULL };
			execve(args[0], args, NULL);
		} else {
			wait(&res);
			res = WEXITSTATUS(res);
			printf("xor result: %d\n", res);
		}
	} while (1);
	
	return res;
}
