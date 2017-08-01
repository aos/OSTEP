#include <pthread.h>
#include <stdio.h>
#include <assert.h>

int
main(int argc, char *argv[])
{
    // Create a lock
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

    // Initialize a lock
    int rc = pthread_mutex_init(&lock, NULL); 
    assert(rc == 0); // Check for success

    // Destroy a lock
    pthread_mutex_destroy(&lock);
}

