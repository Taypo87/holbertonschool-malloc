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
	size_t size_ptr;

	if (heap_start == NULL)
		heap_start = sbrk(0);
	if (!unused)
		unused = sysconf(_SC_PAGESIZE);
	if (!chunk_start)
		chunk_start = heap_start;

	while (unused < (size + sizeof(size_t)))
	{
		sbrk(sysconf(_SC_PAGESIZE));
		unused += sysconf(_SC_PAGESIZE);
	}
	while (size % 8 != 0)
	{
		size++;
	}
	ptr = chunk_start;
	chunk_start = (char *)chunk_start + size + sizeof(size_t);
	unused -= size;
	ptr = (char *)ptr + sizeof(size_t);

	return (ptr);
}
