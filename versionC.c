#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "strlib.h"

int main() {
	char str1[STR_LEN], str2[STR_LEN];
	int res = 0, rc;
	int prot = PROT_READ | PROT_WRITE;
	int flags = MAP_SHARED | MAP_ANONYMOUS;
	char *memmap = mmap(NULL, 128, prot, flags, -1, 0);
	
	do {
		printf("Please, Enter string number 1: ");
		fgets(str1, STR_LEN, stdin);
		
		printf("Please, Enter string number 2: ");
		fgets(str2, STR_LEN, stdin);
		
		memcpy(memmap, str1, STR_LEN);
		memcpy(&memmap[STR_LEN + 1], str2, STR_LEN);
		
		rc = fork();
		
		if (rc < 0) {
			fprintf(stderr, "fork failed\n");
			exit(1);
		} else if (rc == 0) {
			char firstStr[STR_LEN], secondStr[STR_LEN];
			
			strcpy(firstStr, memmap);
			strcpy(secondStr, &memmap[STR_LEN + 1]);
			
			res = strxor(firstStr, secondStr);
			printf("xor result: %d\n", res);
		} else {
			wait(&res);
			res = WEXITSTATUS(res);
			printf("xor result: %d\n", res);
		}
	} while (1);
	
	return 0;
}
