#include <errno.h>
#include <string.h>
#include <sys/mman.h>
#include <stdio.h>
#include "oneshot.h"

size_t allocations_head = 0;
allocation allocations[MAX_ALLOCATIONS] = {0};

void* dom_malloc(size_t bytes){
    if (allocations_head >= MAX_ALLOCATIONS){
        errno = ENOMEM; 
        return NULL;
    }

    void* addr = NULL;

    for (size_t i = 0; i < MAX_ALLOCATIONS; ++i){
        if (i == allocations_head || allocations[i].free){
            addr = mmap(
                NULL, 
                bytes, 
                PROT_READ | PROT_WRITE, 
                MAP_PRIVATE | MAP_ANONYMOUS,
                -1,
                0
            );

            if (addr == MAP_FAILED){
                return addr;
            }

            allocations[i] = (allocation) {
                .addr = addr,
                .bytes = bytes,
                .free = 0
            }; 

            if (i == allocations_head){
                ++allocations_head;
            }

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
