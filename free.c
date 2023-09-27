#include "malloc.h"

void _free(void *ptr)
{
    headers *header;

    if (ptr)
    {
        header = ((struct headers*)ptr) - 1;
        header->my_size = 0;
    }
}
