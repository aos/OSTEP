#include <stdio.h>

int
main(int argc, char *argv[])
{
    int *p = NULL;
    int x = *p;

    printf("Referencing integer pointer 'p': %d\n", x);

    return 0;
}
