// Producer-consumer (bounded buffer) problem using semaphores

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX (1)

int buffer[MAX];
int fill = 0;
int use  = 0;

void put(int value) {
  buffer[fill] = value;
  fill = (fill + 1) % MAX;
}

int get() {
  int tmp = buffer[use];
  use = (use + 1) % MAX;
  return tmp;
}

sem_t empty,
      full,
      mutex;

void *producer(void *arg) {

  int loops = (int) arg;

  int i;
  for (i = 0; i < loops; i++) {
    sem_wait(&empty);

    sem_wait(&mutex); // Move binary semaphore (lock) around actual data
    put(i);
    sem_post(&mutex);

    sem_post(&full);
  }

  return NULL;
}

void *consumer() {
  int tmp = 0;
  while (tmp != -1) {
    sem_wait(&full);

    sem_wait(&mutex);
    tmp = get();
    sem_post(&mutex);

    sem_post(&empty);
    printf("%d\n", tmp);
  }

  return NULL;
}

int
main(int argc, char *argv[]) {
  // ...
  sem_init(&empty, 0, MAX); // MAX buffers are empty to begin with...
  sem_init(&full, 0, 0);
  sem_init(&mutex, 0, 1); // mutex initialized to 1 because it is a lock
}
