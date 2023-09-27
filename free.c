#include "malloc.h"
/*
* _free - frees a chunk of memory allocated by _malloc
* @ptr: pointer to the memory to be freed
*/
void _free(void *ptr)
{
	headers *header;

	if (ptr)
	{
		header = ((struct headers*)ptr) - 1;
		header->my_size = 0;
	}
}
