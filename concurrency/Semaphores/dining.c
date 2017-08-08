#include <stdio.h>
#include <semaphore.h>

/*
 * Dining philosopher's problem
 *
 * Five philosophers sitting around a table
 * Between each pair of philosophers is a single fork (thus, five total)
 * Each have times where they think, don't need forks
 * In order to eat, philosopher needs two forks (both one on right and left)
 *
 * Write routines getforks() and putforks() with no deadlock,
 * no starving, and high concurrency.
*/

// When philosopher 'p' wishes to refer to fork on left
int left(int p) { 
  return p;
}

// When philosopher 'p' wishes to refer to fork on right
// Modulo operator handles case where p=4 tries to grab fork 0
int right(int p) {
  return (p + 1) % 5;
}

sem_t forks[5];

// The solution is to have the last philosopher
// Acquire the forks in a different order
void getforks() {
  if (p == 4) {
    sem_wait(forks[right(p)]);
    sem_wait(forks[left(p)]);
  }
  else {
    sem_wait(forks[left(p)]);
    sem_wait(forks[right(p)]);
  }
}

void putforks() {
  sem_post(forks[left(p)]);
  sem_post(forks[right(p)]);
}
