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
typedef struct _node {
  char *value;
  struct _node *next;
} node;

// Hash table
node *hashtable[MAXSIZE];

// Create a new list
node* create(char *string) {
  // Malloc new node
  node *new_node = malloc(sizeof (node));
  
  if (new_node == NULL) {
    fprintf(stderr, "Not enough memory to allocate new list.\n");
  }
  // Initialize values
  new_node->value = string;
  new_node->next = NULL;

  return new_node;
}

void insert(char *value) {

  // Create new node
  node *new_node = create(value);
  // Hash it
  size_t index = hash(value);

  // Insert into hash table
  new_node->next = hashtable[index]; // *(table + index)
  hashtable[index] = new_node;
}

void *worker(void *value) {
  insert(value);

  return NULL;
}

bool find(const char *check) {

  // Get hash key for word
  size_t index = hash(check);

  // Store value of node at hashtable[index] (if exists)
  node *checker = hashtable[index];

  while (checker) {

    if (strcasecmp(check, checker->value) == 0) {
      // Found value
      return true;
    }
    checker->next = checker;

  }
  // Did not find value
  return false;
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
