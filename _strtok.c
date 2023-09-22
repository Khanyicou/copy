#include <stddef.h>
#include "shell.h"

/**
 * strtokqe - string token with quotes and escapes
 * @str: string
 * @delim: delimiters
 * @escflags: escape flags (bitwise)
 *            1 - Use \ to escape delimiters
 *            2 - Single quotes skip
 *            4 - Double quotes skip
 * Return: string
 */
char *strtokqe(char *str, char *delim, int escflags)
{
static char *saved_string;
char *token;
int i = 0, j;

if (str == NULL)
str = saved_string;

while (str[i] != '\0')
{
if ((escflags & 1) && str[i] == '\\')
{
if (str[i + 1] != '\0')
i++;
}
else if ((escflags & 2) && str[i] == '\'')
{
i++;
while (str[i] != '\'' && str[i] != '\0')
{
if ((escflags & 1) && str[i] == '\\')
{
if (str[i + 1] != '\0')
i++;
}
i++;
}
}
else if ((escflags & 4) && str[i] == '"')
{
i++;
while (str[i] != '"' && str[i] != '\0')
{
if ((escflags & 1) && str[i] == '\\')
{
if (str[i + 1] != '\0')
i++;
}
i++;
}
}
else
{
j = 0;
while (delim[j] != '\0')
{
if (str[i] == delim[j])
break;
j++;
}
if (delim[j] != '\0')
break;
}
i++;
}

if (str[i] != '\0')
{
str[i] = '\0';
token = str;
saved_string = str + i + 1;
}
else
{
token = str;
saved_string = NULL;
}

return (token);
}
