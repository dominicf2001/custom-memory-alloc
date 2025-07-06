#include <sys/mman.h>
#include <string.h>
#include "bump.h"

int main(){

    // TESTS
    
    // simple allocation
    {
        const char* str = "Hello world"; 
        char* str_heap = dom_malloc(sizeof(char) * (strlen(str) + 1));
    }


    return 0;
}
