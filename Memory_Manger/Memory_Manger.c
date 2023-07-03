#include <stdio.h>
#include <string.h>
#include"Memory_Manger.h"

void mm_pool_init(struct mm_pool* pool)
{
    unsigned int index_i= 0;
    memset(pool->memory, 0, MEM_SIZE(pool->block_size, pool->nr_blocks));
    pool->first_free= (struct mm_block_hdr*)pool->memory;

    struct mm_block_hdr* current_block= pool->first_free;
    for(; index_i < pool->nr_blocks-1; index_i++)
    {
        current_block->next= (struct mm_block_hdr *)((char *)(current_block + 1) + pool->block_size);    
        current_block= current_block->next;
        pool->nr_free_blocks++;
    }
    current_block->next= NULL;
    pool->nr_free_blocks++;
}

void* mm_allocate(struct mm_pool* pool)
{

}

void mm_free(void* data, struct mm_pool* pool)
{

}

void mm_show_stats(struct mm_pool* pool)
{
    printf("Number of free= %d\n", pool->nr_free_blocks);
    struct mm_block_hdr* block= pool->first_free;
    while(block != NULL)
    {
        printf("%p\n", block);
        block= block->next;
    }
}