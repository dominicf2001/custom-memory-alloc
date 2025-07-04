#include <errno.h>
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
    if (allocations_i >= MAX_ALLOCATIONS){
        errno = ENOMEM; 
        return NULL;
    }

    void* addr = NULL;

    for (int i = 0; i < MAX_ALLOCATIONS; ++i){
        if (i == allocations_i || allocations[i].free){
            addr = mmap(
                NULL, 
                len, 
                PROT_READ | PROT_WRITE, 
                MAP_PRIVATE | MAP_ANONYMOUS,
                -1,
                0
            );

            if ((size_t) addr == -1){
                return addr;
            }

            allocations[i] = (dom_allocation) {
                .addr = addr,
                .len = len,
                .free = 0
            }; 

            if (i == allocations_i){
                ++allocations_i;
            }

            break;
        }
    }

    return addr;
}

int dom_free(void* addr){
    for (int i = 0; i < allocations_i; ++i){
        if (allocations[i].addr == addr){
            int code = munmap(allocations[i].addr, allocations[i].len);
            allocations[i].addr = NULL; 
            allocations[i].free = 1;
            allocations[i].len = 0;
            return code;
        }
    }
    
    errno = EFAULT;
    return -1;
}

void dom_debug_print(){
    for (int i = 0; i < allocations_i; ++i){
        printf("(p: %p | free: %d | len: %zu), ", allocations[i].addr, allocations[i].free, allocations[i].len);
    }

    printf("\n");
}
