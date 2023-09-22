#ifndef SHELLVARH
#define SHELLVARH

/**
 * struct ShellVar - shellvar list node
 * @name: name of var
 * @val: value of var
 * @next: the variable that follows next
 */
typedef struct ShellVar
{
	char *val;
	char *name;
	struct ShellVar *next;
} ShellVar;

#endif
