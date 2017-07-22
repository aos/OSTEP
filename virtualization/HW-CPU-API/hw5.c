#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for "getpid()"
#include <sys/wait.h>
#include <sys/types.h>

int
main(int argc, char *argv[])
{
    pid_t rc = fork();
    printf("This is parent process (pid: %d)\n", (int) getpid());

    if (rc < 0) {
        // Fork failed; exit
        fprintf(stderr, "fork failed\n");
        return 1;
    }
    else if (rc == 0) {
        printf("This is child process (pid: %d)\n", (int) getpid());
        int w2 = wait(NULL);

        printf("What happens if we wait in child? This is w2: %d\n", w2);
    }
    else {
        int wc = waitpid(rc, NULL, 0);

        printf("This is parent process after waiting. (pid: %d)\n", (int) getpid());
        printf("This is child pid: %d\n", rc);
        printf("wait() return value: %d\n", wc); // Wait returns child process ID
    }
}
