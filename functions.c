#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int argsxorstr(char *arg1, char *arg2) {
	int lenArg1 = (int)strlen(arg1);
	int lenArg2 = (int)strlen(arg2);
	int maxLen = lenArg1 > lenArg2 ? lenArg1 : lenArg2;
	int i, res = 0;
	
	char *str1 = (char*)calloc(maxLen, maxLen * sizeof(char));
	if (!str1) 
		return EXIT;
	strcpy(str1, arg1);
	
	char *str2 = (char*)calloc(maxLen, maxLen * sizeof(char));
	if (!str2) 
		return EXIT;
	strcpy(str2, arg2);
	
	for (i = 0; i < maxLen; i++) {
		res ^= str1[i] ^ str2[i];
	}

	return res;
}

void xorstr() {
	char str1[STR_LEN], str2[STR_LEN];
	
	while (!feof(stdin)) {
		fgets(str1, STR_LEN, stdin);
		fgets(str2, STR_LEN, stdin);

		printf("%d\n", argsxorstr(str1, str2));
		fflush(stdout);
	}
}
