#include <stdio.h>
#include <errno.h>
#include <sys/mman.h>

// -------------
// MEMORY
// -------------

#define MEM_SIZE 1 << 20 // 1MB

void* memory_head = NULL; 
void* memory = NULL;

void* memory_init(){
    if (memory != NULL){
        errno = EPERM;
        return (void*) -1;
    }

    memory_head = memory = mmap(NULL, MEM_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if ((size_t) memory == -1){
        return memory;
    }

    return memory;
}

// -------------

// -------------
// ALLOCATIONS 
// -------------

#define MAX_ALLOCATIONS 100

typedef struct allocation {
    void* addr;
    size_t bytes;
    int free;
} allocation;

size_t allocations_head = 0;
allocation allocations[MAX_ALLOCATIONS];

// -------------


// -------------
// IMPLEMENTATIONS 
// -------------

void* dom_malloc(size_t bytes){
    if (memory == NULL){
        memory_init();
    } 

    if ((memory_head + bytes) - memory >= MEM_SIZE){
        errno = ENOMEM;
        return NULL;
    }

    void* addr = NULL;

    for (size_t i = 0; i < MAX_ALLOCATIONS; ++i){
        if (i == allocations_head || allocations[i].free){
            addr = memory_head; 
            allocations[i] = (allocation) {
                .addr = addr, 
                .bytes = bytes,
                .free = 0,
            }; 

            if (i == allocations_head){
                ++allocations_head;
            }

            memory_head = memory_head + bytes;

            break;
        }
    }

    return addr;
}

int dom_free(void* addr){
    for (size_t i = 0; i < allocations_head; ++i){
        if (allocations[i].addr == addr){
            int code = munmap(allocations[i].addr, allocations[i].bytes);
            allocations[i].addr = NULL; 
            allocations[i].free = 1;
            allocations[i].bytes = 0;
            return code;
        }
    }
    
    errno = EFAULT;
    return -1;
}

void dom_debug_print(){
    for (size_t i = 0; i < allocations_head; ++i){
        printf("(p: %p | free: %d | len: %zu), ", allocations[i].addr, allocations[i].free, allocations[i].bytes);
    }

    printf("\n");
}

// -------------
