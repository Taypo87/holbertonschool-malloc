#include "malloc.h"


void *naive_malloc(size_t size)
{
    size_t *ptr;

    ptr = (size_t *)sbrk(0);
    sbrk(size + sizeof(size_t));
    
    return (void *)(ptr + 1);
}
