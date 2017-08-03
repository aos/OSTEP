// Simple implementation of a spin-lock

#include <stdio.h>

// Test and set instruction
// Returns old value pointed by the 'ptr' and updates said value to new
int TestAndSet(int *old_ptr, int new) {
    int old = *old_ptr; // Fetch old value at old_ptr
    *old_ptr = new;     // Store 'new' into old_ptr
    return old;
}

// Our lock
typedef struct __lock_t {
    int flag;
} lock_t;

void init(lock_t *lock) {
    // 0 indicates that lock is available, 1 that it is held
    lock->flag = 0;
}

void lock(lock_t *lock) {
    while (TestAndSet(&lock->flag, 1) == 1)
        ; // spin-wait (do nothing)
}

void unlock(lock_t *lock) {
    lock->flag = 0;
}

int
main(int argc, char *argv[])
{

    

}
