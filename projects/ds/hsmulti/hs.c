/*
 * Thread-safe concurrent hash table implementation
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>

#define MAXSIZE (1013)

// Hash function
size_t hash(const char *str) {
  size_t hash = 5381;

  for (int i = 0; str[i] != '\0'; i++) {
    hash += hash * 33 + (int) str[i];
  }
  return hash % MAXSIZE;
}

// Linked list node
typedef struct _node_l {
  char             *value;
  struct _node_l   *next;
} node_l;

// Linked list struct
typedef struct _list_l {
  node_l            *head;
  int               count;
  pthread_mutex_t   lock;
} list_l;

// Initialize a list
list_l *list_init() {
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
list_l *hashtable[MAXSIZE];

// Create a new node
node_l* create(char *value) {
  // Malloc new node
  node_l *new_node = malloc(sizeof (node_l));
  
  if (new_node == NULL) {
    fprintf(stderr, "Unable to allocate memory for new node.\n");
  }

  // Initialize values
  new_node->value = value;
  new_node->next = NULL;

  return new_node;
}

void insert(char *value) {
  // Create new node
  node_l *new_node = create(value);
  // Get hash index 
  size_t index = hash(value);
  
  // Initialize list at hash table index 
  if (hashtable[index] == NULL) {
    list_l *new_list = list_init();

    // Lock critical section
    pthread_mutex_lock(&new_list->lock);

    new_node = new_list->head;
    new_list->head = new_node;
    hashtable[index] = new_list;

    pthread_mutex_unlock(&new_list->lock);
  } 

  // Lock critical section
  pthread_mutex_lock(&hashtable[index]->lock);

  new_node->next = hashtable[index]->head; 
  hashtable[index]->head = new_node;

  pthread_mutex_unlock(&hashtable[index]->lock);
}

char* find(const char *check) {

  // Get hash key
  size_t index = hash(check);

  // Lock at hashtable index
  pthread_mutex_lock(&hashtable[index]->lock);

  // Store value of node at hashtable[index] (if exists)
  node_l *checker = hashtable[index]->head;

  while (checker) {
    if (strcasecmp(check, checker->value) == 0) {

      pthread_mutex_unlock(&hashtable[index]->lock);
      // Found value
      return checker->value;
    }
    checker->next = checker;
  }

  pthread_mutex_unlock(&hashtable[index]->lock);
  // Did not find value
  return NULL;
}

void *worker(void *value) {

  return NULL;
}

int
main(int argc, char *argv[])
{
  char *aos[2]; 

  aos[0] = "Hi there!";
  aos[1] = "YES THIS IS NOT SIMILAR TO THE OTHER STRING";

  void *ret;

  pthread_t p[2];

  for (int j = 0; j < 2; j++) {
    pthread_create(&p[j], NULL, worker, aos[j]);
    pthread_join(p[j], &ret); 

    printf("Value = %s\n", (char *) ret);
  }

  return 0;
}
