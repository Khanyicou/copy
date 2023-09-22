#include <stdlib.h>
#include "shell.h"

/**
 * _realloc - reallocates a memory block using malloc and free
 * @ptr: pointer to the previously allocated memory
 * @old_size: size of the old memory block
 * @new_size: size of the new memory block
 * Return: pointer to the reallocated memory block
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
void *new_ptr;

if (new_size == old_size)
return (ptr);

if (new_size == 0)
{
free(ptr);
return (NULL);
}

new_ptr = malloc(new_size);

if (new_ptr == NULL)
{
free(ptr);
return (NULL);
}
if (ptr != NULL)
{
char *src = ptr;
char *dest = new_ptr;
unsigned int i;

for (i = 0; i < old_size && i < new_size; i++)
dest[i] = src[i];

free(ptr);
}

return (new_ptr);
}
