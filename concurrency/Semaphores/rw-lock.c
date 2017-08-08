// Read-write lock using semaphores

#include <stdio.h>
#include <semaphore.h>

typedef struct _rwlock_t {
  sem_t lock;       // Binary semaphore (basic lock)
  sem_t writelock;  // Used to allow ONE write or MANY readers 
  int   readers;    // Count of readers reading in critical section
} rwlock_t;

void rwlock_init(rwlock_t *rw) {
  rw->readers = 0;
  sem_init(&rw->lock, 0, 1);
  sem_init(&rw->writelock, 0, 1);
}

void rwlock_acquire_readlock(rwlock_t *rw) {
  sem_wait(&rw->lock);
  rw->readers++;
  if (rw->readers == 1) {
    sem_wait(&rw->writelock);   // First reader acquires writelock
  }
  sem_post(&rw->lock);
}

void rwlock_release_readlock(rwlock_t *rw) {
  sem_wait(&rw->lock);
  rw->readers--;
  if (rw->readers == 0) {
    sem_post(&rw->writelock);   // Last reader releases writelock
  }
  sem_post(&rw->lock);
}

void rwlock_acquire_writelock(rwlock_t *rw) {
  sem_wait(&rw->writelock);
}

void rwlock_release_writelock(rwlock_t *rw) {
  sem_post(&rw->writelock);
}
