#include <stdio.h>
#include <stdlib.h>

#include "strlib.h"

int main(int argc, char* argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Usage: %s [str1] [str2]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	return strxor(argv[1], argv[2]);
}
