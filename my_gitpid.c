/**
 * my_getpid - gets the pid of the current process
 * Return: string containing the pid
 */
char *my_getpid()
{
char *pid_str = NULL;
pid_t pid = getpid();

if (pid > 0)
{
pid_str = malloc(16);
if (pid_str != NULL)
{
snprintf(pid_str, 16, "%d", pid);
}
}

return (pid_str);
}
