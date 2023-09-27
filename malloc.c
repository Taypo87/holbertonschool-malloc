#include "malloc.h"
/**
* _malloc - allocates memory
* @size: size of memory to allocate
* Return: pointer to allocated memory
*/

void *_malloc(size_t size)
{
	headers *header;
	void *ptr = NULL;
	static void *heap_start, *chunk_start, *chunks[MAX_BLOCKS];
	static size_t unused, total_chunks;
	size_t i;


	if (!heap_start)
	{
		heap_start = sbrk(0);
		unused = sysconf(_SC_PAGESIZE);
		sbrk(sysconf(_SC_PAGESIZE));
		chunk_start = heap_start;
		total_chunks = 0;
	}
	while (size % 8 != 0)
	{
		size++;
	}
	if (total_chunks)
	{
		for (i = 0; i < total_chunks; i++)
		{
			header = ((struct headers*)chunks[i]) - 1;
			if (header->my_size == 0 && header->chunk_size >= size + sizeof(headers))
			{
				header->my_size = size;
				return (chunks[i]);
			}
		}
	}
	while (unused < (size + sizeof(headers)))
	{
		sbrk(sysconf(_SC_PAGESIZE));
		unused += sysconf(_SC_PAGESIZE);
	}
	total_chunks++;
	ptr = chunk_start;
	chunk_start = (char *)chunk_start + size + sizeof(headers);
	header = (struct headers *)ptr;
	header->my_size = size;
	header->chunk_size = size + sizeof(headers);
	unused -= (size + sizeof(headers));
	*((size_t *)ptr) = size;
	ptr = (char *)ptr + sizeof(headers);
	chunks[total_chunks - 1] = ptr;

	return (ptr);
}
