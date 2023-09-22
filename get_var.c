/**
 * init_shellvars - initializes shell variables
 * Return: initialized shell variables
 */
ShellVars *init_shellvars()
{
ShellVars *shellvars = malloc(sizeof(ShellVars));
if (shellvars != NULL)
{
shellvars->special = NULL;
shellvars->vars = NULL;
}
return (shellvars);
}

/**
 * get_special_vars - gets the special shell variables
 * @shellvars: the shell variables struct
 * Return: address of special shell variables
 */
ShellVar *get_special_vars(ShellVars *shellvars)
{
if (shellvars != NULL)
{
return (shellvars->special);
}
return (NULL);
}

/**
 * get_vars - gets the shell variables
 * @shellvars: the shell variables struct
 * Return: address of shell variables
 */
ShellVar *get_vars(ShellVars *shellvars)
{
if (shellvars != NULL)
{
return (shellvars->vars);
}
return (NULL);
}
