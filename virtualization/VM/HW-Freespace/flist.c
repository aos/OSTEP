#include <stdio.h>
#include <sys/mman.h>       // For mmap()

int
main(int argc, char *argv[])
{
    // Initialize free list structure
    typedef struct __node_t {
        int     size;
        struct  __node_t *next;
    } node_t;

    // Initialize the heap
    // Put first element of the free list inside that space
    
    // mmap() returns a pointer to a chunk of free space
    node_t *head = mmap(NULL, 4096, PROT_READ|PROT_WRITE,
                        MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);

    head->size = 4096 - sizeof(node_t);
    head->next = NULL;
}
