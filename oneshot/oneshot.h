#ifndef ONESHOT_H 

#include <string.h>
#include <sys/mman.h>

#define MAX_ALLOCATIONS 100

typedef struct dom_block {
    void* addr;
    size_t bytes;
    int free;
} allocation;

void* dom_malloc(size_t bytes);

int dom_free(void* addr);

void dom_debug_print();

#endif /* oneshot.h */
