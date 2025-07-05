#include <sys/mman.h>
#include <string.h>
#include "mem.h"

int main(){
    const char* str = "Hello world"; 
    char* str_heap = dom_malloc(sizeof(char) * (strlen(str) + 1));
    char* str_heap_two = dom_malloc(sizeof(char) * (strlen(str) + 1));
    dom_debug_print();
    // dom_free(str_heap);
    // dom_debug_print();
    // char* str_heap_three = dom_malloc(sizeof(char) * (strlen(str) + 1));
    // dom_debug_print();
    // char* str_heap_four = dom_malloc(sizeof(char) * (strlen(str) + 1));
    // dom_debug_print();

    return 0;
}
