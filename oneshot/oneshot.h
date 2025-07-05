#ifndef ONESHOT_H 

#include <string.h>
#include <sys/mman.h>

void* dom_malloc(size_t bytes);

int dom_free(void* addr);

void dom_debug_print();

#endif /* oneshot.h */
