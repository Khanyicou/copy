#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alias.h"
#include "shell.h"

static AliasData *aliasList = NULL;

/**
 * getalist - Get the address of the alias list
 * @return: Address of the alias list
 */
AliasData **getalist()
{
return (&aliaslist);
}

/**
 * findalias - Find an alias by name
 * @name: Name of the alias
 * @return: Pointer to the alias if found, otherwise NULL
 */
AliasData *findalias(char *name)
{
AliasData *current = aliasList;

while (current != NULL)
{
if (strcmp(current->name, name) == 0)
{
return (current);
}
current = current->next;
}

return (NULL);
}

/**
 * printAliases - Print all aliases
 */
void printAliases
{
AliasData *current = aliasList;

while (current != NULL)
{
printf("%s='%s'\n", current->name, current->value);
current = current->next;
}
}

/**
 * setalias - Set an alias
 * @name: Name of the alias
 * @value: Value of the alias
 * @return: 0
 */
int setalias(char *name, char *val)
{
 AliasData *existingAlias = findAlias(name);

if (existingAlias != NULL)
{
free(existingAlias->value);
existingAlias->value = strdup(value);
if (existingAlias->value == NULL)
{
return (-1);
}
}
else
{
AliasData *newAlias = malloc(sizeof(AliasData));
if (newAlias == NULL)
{
return (-1);
}
newAlias->name = strdup(name);
newAlias->value = strdup(value);
if (newAlias->name == NULL || newAlias->value == NULL)
{
free(newAlias->name);
free(newAlias->value);
free(newAlias);
return (-1)
}
newAlias->next = aliasList;
aliasList = newAlias;
}
return (0);
}

/**
 * unsetalias - Unset an alias
 * @name: Name of the alias to unset
 * @return: (0) 
 */
int unsetalias(char *name)
{
AliasData *current = aliasList;
AliasData *prev = NULL;

while (current != NULL)
{
if (strcmp(current->name, name) == 0)
{
if (prev != NULL)
{
prev->next = current->next;
}
else
{
aliasList = current->next;
}
free(current->name);
free(current->value);
free(current);
return 0;
}
prev = current;
current = current->next;
}

return (-1);
}

/**
 * aliascmd - Tokenizes arguments for the alias command
 * @av: Arguments
 * @return: (0)
 */
int aliascmd(char *av[])
{
if (av[1] == NULL)
{
printAliases();
return (0);
}

for (int i = 1; av[i] != NULL; i++)
{
char *name = strtok(av[i], "=");
char *value = strtok(NULL, "=");

if (value == NULL)
{
AliasData *alias = findAlias(name);
if (alias == NULL)
{
fprintf(stderr, "alias: %s not found\n", name);
}
else
{
printf("%s='%s'\n", alias->name, alias->value);
}
}
else
{
if (setAlias(name, value) == -1)
{
fprintf(stderr, "Error setting alias: %s='%s'\n", name, value);
return (-1);
}
}
}

return (0);
}
