#include <stdio.h>
#include <signal.h>

void handle(int arg) {
  printf("Stop wakin' me up...\n");
}

int
main(int argc, char **argv) {
  signal(SIGHUP, handle);

  while (1)
    ; // Do nothing until a signal is called

  return 0;
}
