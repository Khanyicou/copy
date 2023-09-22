#include <unistd.h>
#include "shell.h"

/**
 * _putchar - writes a character to stdout
 * @c: The character to print
 * Return: On success, the character written is returned
 */
int _putchar(char c)
{
return (write(1, &c, 1));
}

/**
 * _printenv - print the environment variables
 * Return: 0 on success
 */
int _printenv(void)
{
_printenv
int i = 0;

while (environ[i] != NULL)
{
int j = 0;
while (environ[i][j] != '\0')
{
_putchar(environ[i][j]);
j++;
}
_putchar('\n');
i++;
}
return (0);
}
