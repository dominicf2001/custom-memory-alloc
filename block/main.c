#include <sys/mman.h>
#include <string.h>
#include <sys/types.h>

#define BLOCK_SIZE 64
#define POOL_SIZE (BLOCK_SIZE * 1000)
#define NUM_OF_BLOCKS (POOL_SIZE / BLOCK_SIZE)

int main(){
    void* pool = mmap(NULL, POOL_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);  
    u_int8_t* pool_base = pool;

    void* free_list = pool;
 
    // init
    for (size_t i = 0; i < NUM_OF_BLOCKS; ++i){
        void* current_block = &pool_base[i * BLOCK_SIZE];
        void* next_block = &pool_base[(i + 1) * BLOCK_SIZE];
        *(void**)current_block = next_block;
    }

    return 0;
}
