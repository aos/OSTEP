/*
 * Thread-safe concurrent hash table implementation
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

void insert(node **table, char *value) {

  // Create new node
  node *new_node = create(value);
  // Hash it
  size_t index = hash(value);

  // Insert into hash table
  if (table[index] == NULL) {
    table[index] = new_node; 
  } 
  else {
    new_node->next = table[index]; // *(table + index)
    table[index] = new_node;
  }
}

void *worker(void *table, void *value) {
  insert(table, value);

  return NULL;
}

int
main(int argc, char *argv[])
{
  node *hashtable[MAXSIZE];
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
