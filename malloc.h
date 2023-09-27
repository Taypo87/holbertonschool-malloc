#ifndef _MALLOC_
#define _MALLOC_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_BLOCKS 10000

struct headers{
	size_t my_size;
	size_t chunk_size;
};
typedef struct headers headers;


void *naive_malloc(size_t size);
void *_malloc(size_t size);
void _free(void *ptr);

#endif
