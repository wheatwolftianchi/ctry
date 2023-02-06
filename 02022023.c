int main(int argc, char const *argv[])
{
    int a = -2;
    long b = 0x41250f1;
    b <<= (b & -2);
    printf("b=%lx\n", b);
    return 0;
}
