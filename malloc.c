#include "malloc.h"
/**
* _malloc - allocates memory
* @size: size of memory to allocate
* Return: pointer to allocated memory
*/

void *_malloc(size_t size)
{
	struct headers *header;
	void *ptr;
	static void *heap_start, *chunk_start, *heap_end, *chunks[MAX_BLOCKS];
	static size_t unused, total_chunks;
	size_t i;

// start-up code block
	if (!heap_start)
	{
		heap_start = sbrk(0);
		unused = sysconf(_SC_PAGESIZE);
		heap_end = sbrk(sysconf(_SC_PAGESIZE));
		chunk_start = heap_start;
		total_chunks = 0;
	}
	while (size % 8 != 0)
	{
		size++;
	}
// check for available chunks before allocated a new one
	for (i = 0; i <= total_chunks; i++)
	{
		header = (struct headers *)chunks[i] - 1;
		if (header->my_size == 0 && chunk_size >= size + sizeof(headers))
		{
			header->my_size = size;
			return (chunks[i]);
		}
	}
// if we add a new chunk, total_chunks++ to keep our end place in array of pointers

	// code for new chunk
	while (unused < (size + sizeof(size_t)))
	{
		heap_end = sbrk(sysconf(_SC_PAGESIZE));
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

	return (ptr);
}
