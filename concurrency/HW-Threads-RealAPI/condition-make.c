#include <stdio.h>
#include <pthread.h>

int
main(int argc, char *argv[])
{
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

    pthread_mutex_lock(&lock);

    // Condition variables
    // Used for signaling between threads

    // Puts calling thread to sleep
    int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);

}

