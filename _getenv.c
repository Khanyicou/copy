#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

#define SHELL_H

static char *environment[MAX_ENV_VARS];
static int env_count = 0;

char *_getenv(const char *name)
{
for (int i = 0; i < env_count; i++)
{
char *env_var = environment[i];
char *equals = strchr(env_var, '=');
if (equals != NULL)
{
size_t name_len = equals - env_var;
if (strncmp(name, env_var, name_len) == 0)
{
return (equals + 1);
}
}
}
return (NULL);
}

int _setenv(const char *name, const char *value)
{
if (env_count >= MAX_ENV_VARS)
{
return (-1);
}

size_t len = strlen(name) + strlen(value) + 2;
char *env_var = (char *)malloc(len);
if (env_var == NULL)
{
return (-1);
}

snprintf(env_var, len, "%s=%s", name, value);


environment[env_count] = env_var;
env_count++;

return (0);
}

int _unsetenv(const char *name)
{
for (int i = 0; i < env_count; i++)
{
char *env_var = environment[i];
char *equals = strchr(env_var, '=');
if (equals != NULL)
{
size_t name_len = equals - env_var;
if (strncmp(name, env_var, name_len) == 0) 
{
free(environment[i]);
for (int j = i; j < env_count - 1; j++)
{
environment[j] = environment[j + 1];
}
env_count--;
return (0);
}
}
}
return (-1);
}

int main(void)
{
_setenv("NAME", "John");
_setenv("AGE", "30");
_setenv("CITY", "New York");

printf("NAME=%s\n", _getenv("NAME"));
printf("AGE=%s\n", _getenv("AGE"));
printf("CITY=%s\n", _getenv("CITY"));

_unsetenv("AGE");
printf("AGE=%s\n", _getenv("AGE"));

return (0);
}
