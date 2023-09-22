#include <stdlib.h>
#include <unistd.h>

/**
 * _getline - reads a line from a file descriptor
 * @lineptr: pointer to the buffer where the line is stored
 * @fd: file descriptor to read from
 * Return: number of characters read (including newline), 0 on EOF, -1 on error
 */
int _getline(char **lineptr, int fd)
{
if (lineptr == NULL)
return (-1);

size_t size = 1025;
size_t len = 0;
int c;

if (*lineptr == NULL)
{
*lineptr = malloc(size);
if (*lineptr == NULL)
return (-1);
}

while ((c = read(fd, *lineptr + len, 1)) > 0)
{
if ((*lineptr)[len] == '\n')
return (len + 1);
len++;

if (len == size - 1)
{
size += 1024;
char *new_ptr = realloc(*lineptr, size);
if (new_ptr == NULL)
return (-1);
*lineptr = new_ptr;
}
}

if (c == 0 && len == 0)
return (0);

if (c == -1)
return (-1);

return (len);
}
