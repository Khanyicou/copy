#include "shell.h"

/**
 * my_getenviron - get a copy of the environment variables
 *
 * Return: A pointer to the environment variables
 */
char **my_getenviron()
{
static char **environ_copy;

return (environ_copy);
}
