#include <string.h>
#include <sys/mman.h>
#include <stdio.h>

#define MAX_ALLOCATIONS 100

typedef struct dom_allocation {
    void* addr;
    size_t len;
    int free;
} dom_allocation;

int allocations_i = 0;
dom_allocation allocations[MAX_ALLOCATIONS];

void* dom_malloc(size_t len){
    void* addr = mmap(
        NULL, 
        len, 
        PROT_READ | PROT_WRITE, 
        MAP_PRIVATE | MAP_ANONYMOUS,
        -1,
        0
    );

    allocations[allocations_i++] = (dom_allocation) {
        .addr = addr,
        .len = len,
        .free = 0
    };

    return addr;
}

void dom_free(){

}

void dom_debug_print(){
    for (int i = 0; i < allocations_i; ++i){
        printf("%p, ", allocations[i].addr);
    }
}
