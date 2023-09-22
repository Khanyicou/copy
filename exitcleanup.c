#include "shell.h"

/**
 * execute_builtin - executes built-in shell commands
 * @command: The command to execute
 * @arguments: An array of command arguments
 * Return: The exit status of the command
 */
int execute_builtin(char *command, char *arguments[])
{
int exit_status = 0;

if (command == NULL)
return (0);

if (strcmp(command, "exit") == 0)
{
if (arguments[1] != NULL)
{
int exit_code = atoi(arguments[1]);
exit(exit_code);
}
else
{
char *retstr = getsvar("?");
exit_status = atoi(retstr);
free(retstr);
exit(exit_status);
}
}
else if (strcmp(command, "cd") == 0)
{
exit_status = change_directory(arguments);
}
else if (strcmp(command, "history") == 0)
{
exit_status = print_history();
}
else if (strcmp(command, "help") == 0)
{
exit_status = help(arguments[1]);
}
else if (strcmp(command, "env") == 0)
{
exit_status = print_environment();
}
else if (strcmp(command, "setenv") == 0)
{
exit_status = set_environment_variable(arguments);
}
else if (strcmp(command, "unsetenv") == 0)
{
exit_status = unset_environment_variable(arguments[1]);
}
else if (strcmp(command, "alias") == 0)
{
exit_status = alias_command(arguments);
}
else if (strcmp(command, "unset") == 0)
{
exit_status = unset_shell_variable(arguments[1]);
}
else if (strcmp(command, "unalias") == 0)
{
exit_status = unalias_command(arguments[1]);
}
else
{
exit_status = execute_external_command(command, arguments);
}

return (exit_status);
}

/**
 * change_directory - change the current working directory
 * @arguments: An array of command arguments
 * Return: 0 on success, 1 on failure
 */
int change_directory(char *arguments[])
{
char *path = arguments[1] ? arguments[1] : getenv("HOME");

if (!path)
{
printerr("cd: HOME not set\n");
return (1);
{

if (chdir(path) != 0)
{
perror("cd");
return (1);
}

return (0);
}

