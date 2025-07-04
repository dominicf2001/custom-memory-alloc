#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include "./oneshot/oneshot.h"

int main(){
    const char* str = "Hello world"; 
    char* str_heap = dom_malloc(sizeof(char) * (strlen(str) + 1));
    char* str_heap_two = dom_malloc(sizeof(char) * (strlen(str) + 1));

    dom_debug_print();

    return 0;
}
