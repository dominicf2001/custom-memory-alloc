#include "bump.h"
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/mman.h>

// -------------
// MEMORY
// -------------

#define MEM_SIZE (1 << 20) // 1MB

char* memory_head = NULL; 
void* memory = NULL;

void* memory_init(){
    if (memory != NULL){
        errno = EPERM;
        return MAP_FAILED;
    }

    memory_head = memory = mmap(NULL, MEM_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (memory == MAP_FAILED){
        return memory;
    }

    return memory;
}

// -------------

// -------------
// ALLOCATIONS 
// -------------

#define MAX_ALLOCATIONS 1000
#define BLOCK_SIZE 10000

typedef struct allocation {
    void* addr;
    int free;
    size_t bytes;
} allocation;

size_t allocations_head = 0;
allocation allocations[MAX_ALLOCATIONS] = {0};

// -------------


// -------------
// IMPLEMENTATIONS 
// -------------

void* dom_malloc(size_t bytes){
    if (memory == NULL){
        memory_init();
    } 

    if ((size_t) ((memory_head + BLOCK_SIZE) - (char*)memory) >= MEM_SIZE){
        errno = ENOMEM;
        return NULL;
    }

    void* addr = NULL;

    for (size_t i = 0; i < MAX_ALLOCATIONS; ++i){
        addr = memory_head; 
        allocations[allocations_head++] = (allocation) {
            .addr = addr, 
            .free = 0,
            .bytes = bytes
        }; 
        memory_head = memory_head + BLOCK_SIZE;
        break;
    }

    return addr;
}

int dom_free(void *addr){
    for (size_t i = 0; i < MAX_ALLOCATIONS; ++i){
        if (allocations[i].addr == addr){
            allocations[i].free = 1;
        }
    }
}

void dom_debug_print(){
    for (size_t i = 0; i < allocations_head; ++i){
        printf("(p: %p | free: %d), ", allocations[i].addr, allocations[i].free);
    }
    printf("\n");
}

// -------------
