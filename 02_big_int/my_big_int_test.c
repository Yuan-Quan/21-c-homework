#include <stdio.h>
#include "big_int.h"

int main(int argc, char const *argv[])
{
    BigInt *a = big_int_from_ll(-1234);
    BigInt *b = big_int_from_ll(-1234);

    int x = big_int_cmp(a, b);
    return 0;
}
