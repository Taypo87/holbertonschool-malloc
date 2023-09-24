#include "malloc.h"
/**
* _malloc - allocates memory
* @size: size of memory to allocate
* Return: pointer to allocated memory
*/

void *_malloc(size_t size)
{
	void *ptr;
	static void *heap_start, *chunk_start;
	static size_t unused;

	if (heap_start == NULL)
		heap_start = sbrk(0);
	if (!unused	|| unused < size)
	{
		unused += sysconf(_SC_PAGESIZE);
		if (!chunk_start)
			chunk_start = sbrk(sysconf(_SC_PAGESIZE));
		else
			sbrk(sysconf(_SC_PAGESIZE));
	}
	while (unused < size)
	{
		sbrk(sysconf(_SC_PAGESIZE));
		unused += sysconf(_SC_PAGESIZE);
	}
	if (size % 8 != 0)
		size += 8 - (size % 8);

	ptr = chunk_start;
	chunk_start = (char *)chunk_start + size + sizeof(size_t);
	unused -= size;
	*((size_t *)ptr) = size;
	ptr = (char *)ptr + sizeof(size_t);

	return (ptr);
}
