#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

int
main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("USAGE: %s loop-iterations\n", argv[0]);
        return 1;
    }

    char buf;   // Buffer file for read
    struct timeval start, end; // To get seconds and microseconds
    int iterations = atoi(argv[1]);

    gettimeofday(&start, NULL);

    for (int i = 0; i < iterations; i++)
    {
        read(0, &buf, 0);
    }

    gettimeofday(&end, NULL);
    int average = ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)) / iterations;

    printf("Average system call duration: %d microseconds\n", average);            
    return 0;
}
