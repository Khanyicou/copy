/**
 * custom_atoi - Converts a string to an integer.
 * @s: The string input
 *
 * Return: The converted integer
 */
int custom_atoi(char *s)
{
	int result = 0;
	int sign = 1;
	int i = 0;

	/* Handle negative sign if present */
	if (s[0] == '-')
	{
		sign = -1;
		i = 1;
	}

	/* Iterate through the string */
	while (s[i] != '\0')
	{
		/* Check for valid digits */
		if (s[i] >= '0' && s[i] <= '9')
		{
			result = result * 10 + (s[i] - '0');
			i++;
		}
		else
		{
			/* Invalid character encountered, return 0 */
			return (0);
		}
	}

	return (result * sign);
}
