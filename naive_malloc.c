#include "malloc.h"


void *naive_malloc(size_t size)
{
    void *ptr;
    static void *heap_start = NULL, *chunk_start = NULL;
    static size_t unused = 0;

    if (heap_start == NULL || unused < size)
    {
        if (heap_start == NULL)
            heap_start = sbrk(0);
        unused += sysconf(_SC_PAGESIZE);
        chunk_start = sbrk(sysconf(_SC_PAGESIZE));
    }
    if (size % 8 != 0)
        size += 8 - (size % 8);
    
    ptr = chunk_start;
    chunk_start = (char *)chunk_start + size + sizeof(size_t);
    unused =- size;
    *((size_t*)ptr) = size;
    ptr = (char*)ptr + sizeof(size_t);

    return (ptr);
}
