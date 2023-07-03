#include <stdio.h>
#include "Memory_Manger.h"

#define NUMBER_OF_BLOCKS    8
#define BLOCK_SIZE          16
char my_mem[MEM_SIZE(BLOCK_SIZE, NUMBER_OF_BLOCKS)];

struct mm_pool my_pool={
    .memory= my_mem,
    .nr_blocks= NUMBER_OF_BLOCKS,
    .block_size= BLOCK_SIZE
};

int main()
{
    mm_pool_init(&my_pool);
    mm_show_stats(&my_pool);

    void * b1 = mm_allocate(&my_pool);
    mm_show_stats(&my_pool);

    void * b2 = mm_allocate(&my_pool);
    mm_show_stats(&my_pool);

    mm_free(b1, &my_pool);
    mm_show_stats(&my_pool);

    mm_free(b2, &my_pool);
    mm_show_stats(&my_pool);

    return 0;
}