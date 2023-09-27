#ifndef TEST_H
#define TEST_H

#include <stdio.h>

#define TEST(expr) do { \
        if (!(expr)) { \
            printf("\033[1;31mTest failed\033[1;0m: %s\n", #expr); \
        } else {\
            printf("\033[1;32mTest passed\033[1;0m: %s\n", #expr); \
        } \
    } while (0)

#endif
