#ifndef TESTS_H
#define TESTS_H

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define I128(U,V) ((((__uint128_t)(U)) << 64) + (V))

void display_test(char* name, int success);

#endif
