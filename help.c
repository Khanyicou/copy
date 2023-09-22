#include "shell.h"

/**
 * help_builtin - Displays help for built-in commands
 * @cmd: The name of the built-in command (or NULL if no command specified)
 * Return: Always returns 0
 */
int help_builtin(char *cmd)
{
	int r = 0;
	char *file;

	if (cmd == NULL)
	{
		printf("help: no builtin entered.\n");
		return (0);
	}

	if (strcmp(cmd, "cd") == 0 || strcmp(cmd, "history") == 0 ||
		strcmp(cmd, "help") == 0 || strcmp(cmd, "alias") == 0 ||
		strcmp(cmd, "unset") == 0 || strcmp(cmd, "unalias") == 0 ||
		strcmp(cmd, "env") == 0 || strcmp(cmd, "setenv") == 0 ||
		strcmp(cmd, "unsetenv") == 0)
	{
		file = malloc(strlen("help_") + strlen(cmd) + 1);
		if (file == NULL)
			return (-1);
		sprintf(file, "help_%s", cmd);
		r = display_file(file);
		free(file);
	}
	else
	{
		printf("help: no help topics match.\n");
	}

	return (r);
}

/**
 * display_file - Display the contents of a file
 * @filename: The name of the file to display
 * Return: 0 on success
 */
int display_file(char *filename)
{
	FILE *file = fopen(filename, "r");
	char c;

	if (file == NULL)
	{
		perror("display_file");
		return (-1);
	}

	while ((c = fgetc(file)) != EOF)
		putchar(c);

	fclose(file);
	return (0);
}
