#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "strlib.h"

/* Version C: passing child args with mmap */
int main() {
	char str1[STR_LEN + 1], str2[STR_LEN + 1];
	int res = 0, rc;
	char *addr = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, 
				MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	
	if (addr == MAP_FAILED) {
		fprintf(stderr, "map failed\n");
		exit(EXIT_FAILURE);
	}

	printf("Please, Enter string number 1: ");
	mygets(str1, STR_LEN);
	
	printf("Please, Enter string number 2: ");
	mygets(str2, STR_LEN);
	
	rc = fork();
	
	if (rc < 0) {
		fprintf(stderr, "fork failed\n");
		exit(EXIT_FAILURE);
	} else if (rc == 0) {
		res = strxor(addr, &addr[STR_LEN + 1]);
		printf("xor result: %d\n", res);
	} else {
		memcpy(addr, str1, STR_LEN);
		memcpy(&addr[STR_LEN + 1], str2, STR_LEN);
		wait(NULL);
	}

	return EXIT_SUCCESS;
}
