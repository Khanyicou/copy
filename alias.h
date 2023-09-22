#ifndef ALIAS_H
#define ALIAS_H

/**
 * struct AliasData - struct for alias function
 * @name: name of the alias
 * @value: value for the alias
 * @next: pointer to the next alias node
 */
typedef struct AliasData
{
char *name;
char *value;
struct AliasData *next;
}
AliasData;

#endif
