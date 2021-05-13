#include <stdio.h>
#include <stdlib.h>

#include "strlib.h"


int main(int argc, char *argv[]) {
	char str1[STR_LEN + 1], str2[STR_LEN + 1];

	if (argc != 1) {
		fprintf(stderr, "Usage: %s\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	do {
		if (!mygets(str1, STR_LEN))
			break;
		
		if (!mygets(str2, STR_LEN))
			break;
			
		printf("xor result: %d\n", strxor(str1, str2));
		fflush(stdout);
	} while (1);
	
	return EXIT_SUCCESS;
}
