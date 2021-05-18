#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "strlib.h"

/* Version A: passing child args through execve */
int main(int argc, char *argv[]) {
	char str1[STR_LEN], str2[STR_LEN];
	int res = 0, rc;
	
	while (1) { // Run until ctrl + c
		rc = fork();

		if (rc < 0) { /* fork failed */
			fprintf(stderr, "fork failed\n");
			exit(1);
		} else if (rc == 0) { /* child */
			printf("Please, Enter string number 1: ");
			fgets(str1, STR_LEN, stdin);
			
			printf("Please, Enter string number 2: ");
			fgets(str2, STR_LEN, stdin);
			
			char *args[] = {"argsxorstr", str1, str2, NULL };
			execve(args[0], args, NULL);
		} else { /* parent */
			wait(&res); /* Wait to child to end then get the return value of child main */
			res = WEXITSTATUS(res);
			printf("xor result: %d\n", res);
		}
	}
	
	return res;
}
