#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int
main(int argc, char *argv[])
{
    int pipefd[2]; // Create pipe vector (read-end [0], write-end [1])
    char buf; // Buffer to do writing

    pipe(pipefd); // Create pipe to hook read end and write end

    // Create child process 1
    pid_t cpid1 = fork();

    if (cpid1 < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    // Child process 1:
    else if (cpid1 == 0) {
        printf("Child process 1: (pid %d)\n", (int) getpid());
        close(pipefd[0]); // Close unused read-end of this child process

        char *test_write = strdup("Writing stuff to child process 2.");
        write(pipefd[1], test_write, strlen(test_write));
        close(pipefd[1]);

        exit(0);
    } 
    else {
        // Fork child process 2:
        pid_t cpid2 = fork();
        
        if (cpid2 == 0) {
            printf("Child process 2: (pid %d)\n", (int) getpid());
            close(pipefd[1]); // Close unused write-end of this child process

            // read(file descriptor, buffer pointer, size of bytes)
            // Returns number of bytes read, 0 indicates end of file
            while (read(pipefd[0], &buf, 1) > 0) {
                write(STDOUT_FILENO, &buf, 1);
            }
            write(STDOUT_FILENO, "\n", 1);

            close(pipefd[0]);
            exit(0);
        }
        else {
            wait(NULL);
        }
    }
    return 0;
}
