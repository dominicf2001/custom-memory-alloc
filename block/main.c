#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include "block.h"

int main(){
    // {
    //     const char* test_str = "aaaaaaaaaaaaaaaaaaaaaaa";
    //     char* test = dom_malloc(sizeof(strlen(test_str) + 1));
    //     strcpy(test, test_str);
    // }

    {
        const char* test_str = "aaaaaaaaaaaaaaaaaaaaaaa";
        char* test = dom_malloc(10);
        strcpy(test, test_str);

        char* test_two = dom_malloc(10);
        strcpy(test_two, test_str);

        dom_debug_print();

        dom_free(test);
        dom_free(test_two);

        printf("\n");

        dom_debug_print();
    }

    return 0;
}
