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
	if (ft_strncmp(cmd, "cd", 2) == 0 && !cmd[2])
		return (true);
	else if (ft_strncmp(cmd, "echo", 4) == 0 && !cmd[4])
		return (true);
	else if (ft_strncmp(cmd, "pwd", 3) == 0 && !cmd[3])
		return (true);
	else if (ft_strncmp(cmd, "exit", 4) == 0 && !cmd[4])
		return (true);
	else if (ft_strncmp(cmd, "export", 6) == 0 && !cmd[6])
		return (true);
	else if (ft_strncmp(cmd, "unset", 5) == 0 && !cmd[5])
		return (true);
	else if (ft_strncmp(cmd, "env", 3) == 0 && !cmd[3])
		return (true);
	return (false);
}

char	*strjoin_char(char *s1, char c)
{
	char	*str;
	int		i;
	int		len;

	if (s1 == NULL)
		len = 0;
	else
		len = ft_strlen(s1);
	i = 0;
	str = malloc((sizeof(char)) * (len + 2));
	if (!str)
	{
		free(s1);
		return (NULL);
	}
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = '\0';
	free(s1);
	return (str);
}
