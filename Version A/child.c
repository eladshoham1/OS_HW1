#include <stdio.h>
#include "../functions.h"

int main(int argc, char* argv[]) {
	char *arg1 = argv[0];
	char *arg2 = argv[1];

	return argsxorstr(arg1, arg2);
}
