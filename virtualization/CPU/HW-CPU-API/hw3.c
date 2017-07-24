#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
    int rc = fork();

    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0) {
        printf("Hello from child process! %d\n", (int) getpid());
    }
    else {
        int y = 0;
        int x = 100000;
        while (y < x) {
            y += 1;
        }
        int fd = open("./hw3.output2", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
        if (fd < 0) {
            // File open failed; exit
            exit(1);
        }
        if (write(fd, "Write something here\n", 21) == 21) {
            printf("Goodbye from parent process! %d\n", (int) getpid());
        }
    }
    return 0;
}

