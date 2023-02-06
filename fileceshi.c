#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    FILE *fp;
    char ch;
    // create a file named test
    fp = fopen("test", "w");
    unsigned char output;
    // put 4 00 in 1 byte
    output = 0x00;
    fwrite(&output, 1, 1, fp);
    fclose(fp);
    return 0;
}
