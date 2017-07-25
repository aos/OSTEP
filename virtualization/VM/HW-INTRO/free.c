#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
    int *data = (int *)malloc(100 * sizeof(int));

    for (int i = 0; i < 100; i++) {
        data[i] = i + 3;
    }

    free(++data);

    printf("After free(data)\ndata[5] = %d\n", data[5]);

    return 0;
}
