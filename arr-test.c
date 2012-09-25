
/*
 Testing arr macroes.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arr.h"

#define Err() do {printf("%i Error\n", __LINE__); exit(1);} while (0)

typedef struct A
{
    double x, y, z, w;
} A;

void test(void)
{
    {
        arr_init(int, b, 1, 2, 3);
        if (arr_len(b) != 3) Err();
        arr_free(b);
    }
    {
        arr_init_size(int, a, 3);
        if (arr_len(a) != 3) Err();
        arr_free(a);
    }
    {
        arr_init(double, a, 1.2, 1.5);
        if (arr_len(a) != 2) Err();
        if (a[0] != 1.2) Err();
        if (a[1] != 1.5) Err();
        arr_free(a);
    }
    {
        int n = 100;
        arr_init_size(A, a, n);
        if (arr_len(a) != n) Err();
        arr_free(a);
    }
}

int main(int argc, char *argv[])
{
    int i;
    for (i = 0; i < (1 << 1); i++) test();
    printf("Arr unit tests succeeded!\n");
    
    return 0;
}