#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int
main(int argc, char *argv[])
{
    // open() returns the file descriptor (a small integer), if negative, error
    int fd = open("./hw2.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
    if (fd < 0) {
        return 1;
    }

    printf("Parent process: %d\n", (int) getpid());
    printf("File descriptor for hw2.output: %d\n", fd);
    
    int rc = fork();

    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0) {
        // Child:
        printf("Child process: %d\n", (int) getpid());
        printf("File descriptor for hw2.output: %d\n", fd);
        // Write to file given file descriptor 
        int wrote = write(fd, "This will be the output to the file!\n", 37);
        if (wrote != 37) {
            fprintf(stderr, "Error writing to file\n");
            exit(1);
        }
    }
    else {
        // Parent
        printf("Parent process after fork: %d\n", (int) getpid());
        printf("File descriptor after fork: %d\n", fd);

        // Write to file
        int wrote = write(fd, "Can I write to it again?\n", 25);

        if (wrote != 25) {
            fprintf(stderr, "Error writing to file.\n");
            exit(1);
        }

        wait(NULL);
        printf("Wait for null.\n");
    }
    return 0;    
}
