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

typedef struct allocation {
    void* addr;
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

    if (allocations_head > MAX_ALLOCATIONS){
        errno = ENOMEM;
        return NULL;
    }

    if ((size_t) ((memory_head + bytes) - (char*)memory) >= MEM_SIZE){
        errno = ENOMEM;
        return NULL;
    }

    void* addr = memory_head;

    allocations[allocations_head++] = (allocation) {
        .addr = addr, 
        .bytes = bytes,
    }; 
    memory_head = memory_head + bytes;

    return addr;
}

int dom_reset(){
    // reset allocations
    allocations_head = 0;
    memset(allocations, 0, sizeof(allocations));

    // reset memory
    int code = munmap(memory, MEM_SIZE); 
    memory_head = memory = NULL;

    return code;
}

void dom_debug_print(){
    for (size_t i = 0; i < allocations_head; ++i){
        printf("(p: %p | len: %zu), ", allocations[i].addr, allocations[i].bytes);
    }

    printf("\n");
}

// -------------
