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

int	compare_cmd(char *str1, char *str2, int n)
{
	int	i;

	i = 0;
	while ((str1[i] || str2[i]) && i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	if (is_whitespace(str1[i]) || is_quotes(str1[i]) || is_symbol(str1[i]) || !str1[i])
		return (0);
	else
		return (1);
}

bool	is_builtin(char *cmd)
{
	while (cmd && is_whitespace(*cmd))
		cmd++;
	if (compare_cmd(cmd, "cd", 2) == 0)
		return (true);
	else if (compare_cmd(cmd, "echo", 4) == 0)
		return (true);
	else if (compare_cmd(cmd, "pwd", 3) == 0)
		return (true);
	else if (compare_cmd(cmd, "exit", 4) == 0)
		return (true);
	else if (compare_cmd(cmd, "export", 6) == 0)
		return (true);
	else if (compare_cmd(cmd, "unset", 5) == 0)
		return (true);
	else if (compare_cmd(cmd, "env", 3) == 0)
		return (true);
	return (false);
}
