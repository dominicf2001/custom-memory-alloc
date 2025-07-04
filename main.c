#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include "./oneshot/oneshot.h"

int main(){
    const char* str = "Hello world"; 
    char* str_heap = dom_malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(str_heap, str);

    printf("%s", str_heap);

    return 0;
}
