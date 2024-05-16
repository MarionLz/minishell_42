#include "../../include/minishell.h"

bool	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
		return (true);
	return (false);
}

bool	is_symbol(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

int	builtin_cmp(char *str1, char *str2, int n)
{
	int	i;

	i = 0;
	while ((str1[i] || str2[i]) && i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	if (is_whitespace(str1[i]) || is_symbol(str1[i]))
		return (0);
	return (1);
}

bool	is_builtin(char *cmd)
{
	while (cmd && is_whitespace(*cmd))
		cmd++;
	if (builtin_cmp(cmd, "cd", 2) == 0)
		return (true);
	else if (builtin_cmp(cmd, "echo", 4) == 0)
		return (true);
	else if (builtin_cmp(cmd, "pwd", 3) == 0)
		return (true);
	else if (builtin_cmp(cmd, "exit", 4) == 0)
		return (true);
	else if (ft_strncmp(cmd, "export", 6) == 0)
		return (true);
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		return (true);
	else if (builtin_cmp(cmd, "env", 3) == 0)
		return (true);
	return (false);
}
