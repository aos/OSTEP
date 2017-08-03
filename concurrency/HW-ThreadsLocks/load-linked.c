// Load-linked and store-conditional type lock

#include <stdio.h>

// Our lock
typedef struct __lock_t {
    int flag;
} lock_t;

void init(lock_t *lock) {
    lock->flag = 0;
}

// Operates like a typical load instruction
// Fetches value from memory and places it in a register
int LoadLinked(int *ptr) {
    return *ptr;            // Derefenced pointer here
}

// Only succeeds (and updates value stored at address just load-linked from)
// If no intervening store to the address has taken place
int StoreConditional(int *ptr, int value) {
    if (LoadLinked(ptr) == *ptr) {
        *ptr = value; // Sets flag to 1
        return 1; // success
    }
    else {
        return 0; // Failed to update
    }
}

void lock(lock_t *lock) {
    while (1) {
        while (LoadLinked(&lock->flag) == 1)
            ; // Spin until zero
        if (StoreConditional(&lock->flag, 1) == 1)
            return; // If set it to 1 was success - all done
                    // Otherwise: try it all over again
    }
}
