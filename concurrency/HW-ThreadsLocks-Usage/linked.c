// Concurrent linked list

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Basic node structure
typedef struct __node_t {
    int                 key;
    struct __node_t     *next;
} node_t;

// Basic list structure
typedef struct __list_t {
    node_t              *head;
    pthread_mutex_t     lock;
} list_t;

void List_Init(list_t *L) {
    L->head = NULL;
    pthread_mutex_init(&(L->lock), NULL);
}

int List_Insert(list_t *L, int key) {
    node_t *new = malloc(sizeof(node_t)); // Create new node

    if (new == NULL) {
        perror("malloc");
        return -1; // fail
    }

    new->key = key;
    
    // Lock only critical section
    pthread_mutex_lock(&L->lock);
    // Set next to point to old head of list
    new->next = L->head;
    // Set head of list to point to new node
    L->head = new;

    pthread_mutex_unlock(&L->lock);
    return 0; // success
}

int List_Lookup(list_t *L, int key) {
    int rv = -1;
    pthread_mutex_lock(&L->lock);
    node_t *curr = L->head;
    while (curr) {
        if (curr->key == key) {
            rv = 0; // Success
            break;
        }
        curr = curr->next;
    }
    pthread_mutex_unlock(&L->lock);
    return rv; // common return path 
}

// Concurrent hash table

#define BUCKETS (101)

typedef struct __hash_t {
    list_t lists[BUCKETS];
} hash_t;

void Hash_Init(hash_t *H) {
    int i;
    for (i = 0; i < BUCKETS; i++) {
        List_Init(&H->lists[i]);
    }
}

int Hash_Insert(hash_t *H, int key) {
    int bucket = key % BUCKETS;
    return List_Insert(&H->lists[bucket], key);
}

int Hash_Lookup(hash_t *H, int key) {
    int bucket = key % BUCKETS;
    return List_Lookup(&H->lists[bucket], key);
}
