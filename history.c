#include "shell.h"
#include "history.h"

/**
 * init_history - Initialize the history list
 * Return: 0
 */
int init_history(void)
{
HistList **hlistroot = gethistory();
if (*hlistroot == NULL)
{
*hlistroot = NULL;
return (0);
}
return (-1);
}

/**
 * add_to_history - Add a command to the history list
 * @cmd: The command to add
 * Return: 0 on success
 */
int add_to_history(char *cmd)
{
HistList **hlistroot = gethistory();
HistList *new = malloc(sizeof(HistList));
if (new == NULL)
return (-1);

new->cmd = _strdup(cmd);
if (new->cmd == NULL)
{
free(new);
return (-1);
}

new->next = *hlistroot;
*hlistroot = new;
return (0);
}

/**
 * print_history - Print the command history
 * Return: The number of history entries
 */
int print_history(void)
{
HistList **hlistroot = gethistory();
HistList *h = *hlistroot;
int num = 1;

while (h != NULL)
{
printf("%d %s\n", num, h->cmd);
h = h->next;
num++;
}
return (num - 1);
}

/**
 * exit_history - Save history to a file and free memory
 * Return: 1 on success, -1 on failure
 */
int exit_history(void)
{
int fd;
char *file = ".simple_shell_history";
HistList **hlistroot = gethistory();
HistList *h = *hlistroot;
HistList *next;

fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0600);
if (fd == -1)
return (-1);

while (h != NULL)
{
next = h->next;
dprintf(fd, "%s\n", h->cmd);
free(h->cmd);
free(h);
h = next;
}

close(fd);
return (1);
}
