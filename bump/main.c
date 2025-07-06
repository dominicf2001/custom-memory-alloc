#include <sys/mman.h>
#include <string.h>
#include "bump.h"

int main(){

    // TESTS
    
    // simple allocation
    {
        const char* str = "Hello world"; 
        dom_malloc(sizeof(char) * (strlen(str) + 1));
        dom_malloc(sizeof(char) * (strlen(str) + 1));
        dom_reset();
        dom_malloc(sizeof(char) * (strlen(str) + 1));
        dom_debug_print();
    }


    return 0;
}
