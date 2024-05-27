# include "../../include/minishell.h"

bool	is_empty_quotes(char *str)
{
	char quote;

	if (is_quotes(*str))
	{
		quote = *str;
		str++;
		if (*str == quote)
			return (true);
	}
	return (false);
}

void	print_args(char **args, int i)
{
	while (args[i])
	{
		if (!is_empty_quotes(args[i]))
			printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
}

//A voir pour le cas de $=xxxxx
void	ft_echo(char **args)
{
	int i;

	if (compare_cmd(args[1], "-n", 2) == 0)
	{
		i = 2;
		print_args(args, i);
	}
	else
	{
		i = 1;
		print_args(args, i);
		printf("\n");
	}
}
