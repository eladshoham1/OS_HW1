#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "strlib.h"

enum mmapState { ParentRead, ParentWrite, ChildExecute };

/* Version C: passing child args with mmap */
int main() {
	int rc;
	char *addr = (char*)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, 
				MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	
	if (addr == MAP_FAILED) {
		fprintf(stderr, "map failed\n");
		exit(EXIT_FAILURE);
	}
	
	// addr[0] for state
	// addr[1] for result
	// addr[2] for the first string
	// addr[strlen(&addr[2]) + 3] for the second string
	
	addr[0] = ParentRead; // First state, Read 2 string in parent
	rc = fork();
	
	if (rc < 0) {
		fprintf(stderr, "fork failed\n");
		exit(EXIT_FAILURE);
	} 
	
	while (1) { // Run until ctrl + c
		if (rc == 0) {
			if (addr[0] == ChildExecute) {
				addr[1] = strxor(&addr[2], &addr[strlen(&addr[2]) + 3]);
				addr[0] = ParentWrite; // Move to print result in parent
			}
		} else {
			switch(addr[0]) {
				case ParentRead: 
					printf("Please, Enter string number 1: ");
					mygets(&addr[2], STR_LEN);
					
					printf("Please, Enter string number 2: ");
					mygets(&addr[strlen(&addr[2]) + 3], STR_LEN);
					
					fflush(stdin);
					addr[0] = ChildExecute; // Move to execute strxor in child
					break;
				case ParentWrite:
					printf("xor result: %d\n", addr[1]);
					addr[0] = ParentRead; // Stay in parent and read next 2 strings
					break;	
			}
		}
	}

	return EXIT_SUCCESS;
}
