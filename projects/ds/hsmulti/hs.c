/*
 * Thread-safe concurrent hash table implementation
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define HASHSIZE (1013)
#define NUMTHREADS (2)

// Hash function
size_t hash(const char *str) {
  size_t hash = 5381;

  for (int i = 0; str[i] != '\0'; i++) {
    hash += hash * 33 + (int) str[i];
  }
  return hash % HASHSIZE;
}

// Node structure
typedef struct _node_l {
  char             *value;
  struct _node_l   *next;
} node_l;

// Linked list structure
typedef struct _list_l {
  node_l            *head;
  int               count;
  pthread_mutex_t   lock;
} list_l;

// Initialize a list
list_l* list_init() {
  list_l *new_list = malloc(sizeof (list_l));

  if (new_list == NULL) {
    fprintf(stderr, "Unable to allocate memory for new list.\n");
  }

  // Initialize head and lock
  new_list->head = NULL;
  new_list->count = 0;
  pthread_mutex_init(&(new_list->lock), NULL);

  return new_list;
}

// Hash table
list_l *hashtable[HASHSIZE] = {0};

// Create a new node
node_l* create_node(char *value) {
  // Malloc new node
  node_l *new_node = malloc(sizeof (node_l));

  if (new_node == NULL) {
    fprintf(stderr, "Unable to allocate memory for new node.\n");
  }

  // Allocate memory for value
  new_node->value = malloc(sizeof (strlen(value)));
   
  if (new_node->value == NULL) {
    fprintf(stderr, "Unable to allocate memory for value.\n"); 
  }

  // Copy value into node
  strcpy(new_node->value, value);
  new_node->next = NULL;

  return new_node;
}

int insert(char *value) {
  // Create new node
  node_l *new_node = create_node(value);
  // Get hash index
  size_t index = hash(value);
  
  // Initialize list at hash table index 
  if (hashtable[index] == NULL) {
    list_l *new_list = list_init();

    // Lock critical section
    pthread_mutex_lock(&(new_list->lock));

    // new_node = new_list->head;
    new_list->head = new_node;
    new_list->count++;
    hashtable[index] = new_list;

    pthread_mutex_unlock(&(new_list->lock));

    // Success
    return 0;
  } 

  // Lock critical section
  pthread_mutex_lock(&(hashtable[index]->lock));

  new_node->next = hashtable[index]->head; 
  hashtable[index]->head = new_node;
  hashtable[index]->count++;

  pthread_mutex_unlock(&(hashtable[index]->lock));

  return 0;
}

char* find(const char *check) {

  // Get hash key
  size_t index = hash(check);

  // Lock at hashtable index
  pthread_mutex_lock(&(hashtable[index]->lock));

  // Get list head at hashtable[index] (if exists)
  node_l *checker = hashtable[index]->head;

  // Find value in list
  while (checker) {
    if (strcasecmp(check, checker->value) == 0) {

      pthread_mutex_unlock(&(hashtable[index]->lock));
      // Found value
      return checker->value;
    }
    checker->next = checker;
  }

  pthread_mutex_unlock(&(hashtable[index]->lock));
  // Did not find value
  return NULL;
}

void *worker(void *value) {
  printf("Worker thread\n");

  insert(value);
  char *string = find(value);

  return string;
}

int
main(int argc, char *argv[])
{
  char *string[2]; 

  string[1] = "Hi there!";
  string[0] = "Good bye!";

  // Pointers for worker thread return values
  void *ret[NUMTHREADS];

  pthread_t p[NUMTHREADS];

  for (int i = 0; i < NUMTHREADS; i++) {
    pthread_create(&p[i], NULL, worker, string[i]);
  }

  for (int i = 0; i < NUMTHREADS; i++) {
    pthread_join(p[i], &ret[i]); 

    if (ret[i]) {
      printf("Value = %s\n", (char *) ret[i]);
    }
    else {
      fprintf(stderr, "Value not found in table.\n");
    }
  }

  return 0;
}
