// Turn based locks using function FetchAndAdd
// This ensures progress for all threads
#include <stdio.h> 

typedef struct __lock_t {
    int ticket;
    int turn;
} lock_t;

int FetchAndAdd(int *ptr) {
    int old = *ptr;
    *ptr = old + 1;
    return old;
}

void lock_init(lock_t *lock) {
    lock->ticket = 0;
    lock->turn   = 0;
}

void lock(lock_t *lock) {
    int myturn = FetchAndAdd(&lock->ticket);
    while (lock->turn != myturn)
        ; // Spin
}
