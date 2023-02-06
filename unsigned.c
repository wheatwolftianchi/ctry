#include <stdint.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int tx, ty;
    unsigned ux, uy;
    ux = 2147482647U;
    ty = -2147482647;
    tx = (int) ux;
    uy = (unsigned) ty;
    printf("tx = %i ty = %i ux = %u uy = %u\n", tx, ty, ux, uy );
    return 0;
}
