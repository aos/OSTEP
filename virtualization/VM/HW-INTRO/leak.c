#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
    int *p = malloc(sizeof (int));
    int integer;

    printf("Size of integer: %ld\n", sizeof(integer));
    printf("Address to pointer 'p': %p\n", &p);

    return 0;
}
