#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define minFD (0)
#define maxFD (100)

void processFD(int fd) {
  // Process the file descriptor coming in
}

int
main(void) {
  // Open and set up a bunch of sockets
  // Main loop
  while (1) {
    // Initialize the fd_set to all zeroes
    fd_set readFDs;
    FD_ZERO(&readFDs);

    // Now set the bits for the descriptors the server is interested in
    // (For simplicity, all of them from min to max)
    int fd;

    for (fd = minFD; fd < maxFD; fd++) {
      FD_SET(fd, &readFDs);
    }

    // Do the select
    int rc = select(maxFD + 1, &readFDs, NULL, NULL, NULL);

    // Check which actually have data using FD_ISSET()
    for (fd = minFD; fd < maxFD; fd++) {
      if (FD_ISSET(fd, &readFDs)) {
        processFD(fd);
      }
    } 

  }
}
