#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <sched.h>

int
main(int argc, char *argv[])
{
    // Initialize CPU setting
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(0, &set);

    return 0;
}
