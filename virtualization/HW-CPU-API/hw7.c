#include <stdio.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
    printf("Parent process (pid: %d)\n", (int) getpid());
    int rc = fork();

    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        return 1;
    }
    else if (rc == 0) {
        close(STDOUT_FILENO);
        printf("Child process (pid: %d): Hello world!\n", (int) getpid());
    }
    else {
        printf("Back to parent process\n");
    }
}
