#ifndef BUMP_H 

#include <string.h>
#include <sys/mman.h>

void* dom_malloc(size_t bytes);

int dom_reset();

void dom_debug_print();

#endif /* bump.h */
