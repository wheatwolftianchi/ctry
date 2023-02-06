#include <stdio.h>

int main(int argc, char const *argv[])
{
    /* code */
    long x[3];
    char *cp;
    x[2] = 42;
    cp = (char *) x;
    cp += 2*sizeof(long);
    printf("%ld\n", *(long *)cp);
    return 0;
}

