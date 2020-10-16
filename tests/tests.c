#include <stdio.h>
#include "tests.h"

void display_test(char* name, int success){
	printf("%s: %s%s%s\n\n", name, success? ANSI_COLOR_GREEN : ANSI_COLOR_RED, success? "SUCCESS" : "CRITICAL FAILURE", ANSI_COLOR_RESET);
}
