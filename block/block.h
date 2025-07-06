#ifndef BLOCK_H 

#include <string.h>
#include <sys/mman.h>

#define BLOCK_SIZE 64
#define POOL_SIZE (BLOCK_SIZE * 10)
#define NUM_OF_BLOCKS (POOL_SIZE / BLOCK_SIZE)

void* dom_malloc(size_t bytes);

int dom_free(void* addr);

void dom_debug_print();

#endif /* block.h */
