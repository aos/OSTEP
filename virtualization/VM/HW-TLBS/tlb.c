#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define PAGESIZE 8 

int
main(int argc, char *argv[])
{
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <NUMPAGES> <NUM TRIALS>\n", argv[0]);
        return 1;
    }
    
    int NUMPAGES = atoi(argv[1]);
    int NUMTRIALS = atoi(argv[2]);

    int jump = PAGESIZE / sizeof(int);

    int array[NUMPAGES * jump];

    struct timeval start, end; // To get seconds and microseconds
    
    int average = 0;

    for (int i = 0; i < NUMTRIALS; i++) {

        gettimeofday(&start, NULL);

        for (int i = 0; i < NUMPAGES * jump; i += jump) {
            array[i] += 1;    
        }

        gettimeofday(&end, NULL);

        average += ((end.tv_sec * 1000000 + end.tv_sec) - (start.tv_sec * 1000000 + start.tv_usec)) / (NUMPAGES * jump);

    }

    printf("Average cost of accessing NUMPAGES: %d\n", (average / NUMTRIALS));

    return 0;
}
