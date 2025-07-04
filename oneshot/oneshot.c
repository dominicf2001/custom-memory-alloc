#include <string.h>
#include <sys/mman.h>

void* dom_malloc(size_t bytes){
    return mmap(
        NULL, 
        bytes, 
        PROT_READ | PROT_WRITE, 
        MAP_PRIVATE | MAP_ANONYMOUS,
        -1,
        0
    );
}
