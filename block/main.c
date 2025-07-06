#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include "block.h"

int main(){
    {
        const char* testStr = "aaaaaaaaaaaaaaaaaaaaaaa";
        char* test = dom_malloc(sizeof(strlen(testStr) + 1));
        strcpy(test, testStr);
    }

    {
        const char* testStr = "aaaaaaaaaaaaaaaaaaaaaaa";
        char* test = dom_malloc(sizeof(strlen(testStr) + 1));
        strcpy(test, testStr);
    }


    dom_debug_print();

    return 0;
}
