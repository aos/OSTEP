#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int
main(int argc, char *argv[])
{
    int rc = fork();

    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        return 1;
    }
    else if (rc == 0) {
        close(STDOUT_FILENO);
        open("./hw4.output33", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);

        // exec()
        // "v" - Takes an array of arguments, first one being the file
        // "l" - Takes a list of arguments, mutually exclusive with "v" 
        // "p" - Searches the PATH environment variable to find the prog
        // "e" - Extra argument to provide an environment for new prog

        // Now execute ls
        /* char *myargs[2];
        myargs[0] = strdup("ls");
        myargs[1] = NULL;
        execvp(myargs[0], myargs);
        */

        // execlp("ls", ""); // Uses current PATH

        execl("/bin/ls", ""); // Must specify PATH
    }
    else {
        // Parent
        int wc = wait(NULL);
    }
}
