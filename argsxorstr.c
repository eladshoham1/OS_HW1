#include <stdio.h>
#include <stdlib.h>

#include "strlib.h"

int main(int argc, char* argv[]) {
	if (argc != ARVG_ELEMENTS) {
		fprintf(stderr, "Usage: %s\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	return strxor(argv[1], argv[2]);
}
