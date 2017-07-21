#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
    printf("Parent process - (pid: %d)\n", (int) getpid());
    int x = 10;
    printf("Set x = %d\n", x);

    int rc = fork();

    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0) {
        // child:
        printf("Child process: (pid: %d)\n", (int) getpid());
        printf("x = %d\n", x);
        x = 20;
        printf("Set by child process: x = %d\n", x);
    }
    else {
        // Parent:
        printf("Parent process: (pid: %d)\n", (int) getpid());
        printf("Value of x before waiting on child process? %d\n", x);

        int wc = wait(NULL); // Wait for child process to complete

        printf("Waiting on child process: (pid: %d)\n", wc);
        printf("What is the value of x? %d\n", x);
        x = 300;
        printf("Set by parent process: x = %d\n", x);
    }
    return 0;
}
