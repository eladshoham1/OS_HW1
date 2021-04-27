#include <stdio.h>
#include "../functions.h"

int main(int argc, char* argv[]) {
	char *arg1 = argv[1];
	char *arg2 = argv[2];
	int res = argsxorstr(arg1, arg2);

	return res;
}
