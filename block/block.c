#include "block.h"
#include <asm-generic/errno-base.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/mman.h>

void *pool = NULL;
u_int8_t *pool_base = NULL;
void *free_list = NULL;

void dom_init() {
    pool = mmap(NULL, POOL_SIZE, PROT_READ | PROT_WRITE,
                MAP_PRIVATE | MAP_ANON, -1, 0);

    free_list = pool_base = pool;

    for (size_t i = 0; i < NUM_OF_BLOCKS; ++i) {
        int reachedLastBlock = (i == (NUM_OF_BLOCKS - 1));

        void *current_block = &pool_base[i * BLOCK_SIZE];
        void *next_block =
            reachedLastBlock ? NULL : &pool_base[(i + 1) * BLOCK_SIZE];

        *((void **)current_block) = next_block;
    }
}

// -------------
// IMPLEMENTATIONS
// -------------

void* dom_malloc(size_t bytes) {
    if (pool == NULL){
        dom_init();
    }

    void* next_free_block = (*(void**)free_list); 
    if (next_free_block == NULL){
        errno = ENOMEM; 
        return NULL;
    }

    // pop off free list
    void* block = free_list;
    free_list = next_free_block;

    return block; 
}

int dom_free(void *addr) {}

void dom_debug_print() {
    for (size_t i = 0; i < NUM_OF_BLOCKS; ++i){
        void* current_block = &pool_base[i * BLOCK_SIZE];
        printf("Block %zu:", i);
        for (size_t j = 0; j < BLOCK_SIZE; ++j){
            printf("%x ", ((u_int8_t*) current_block)[j]); 
        }
        printf("\n");
    }
}

// -------------
