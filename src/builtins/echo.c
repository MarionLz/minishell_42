# include "../../include/minishell.h"

//A voir pour le cas de $=xxxxx
void	ft_echo(char **args)
{
	int i;

	if (ft_strncmp(args[1], "-n", 2) == 0)
	{
		i = 2;
		while (args[i])
		{
			printf("%s", args[i]);
			if (args[i + 1])
				printf(" ");
			i++;
		}
	}
	else
	{
		i = 1;
		while (args[i])
		{
			printf("%s", args[i]);
			if (args[i + 1])
				printf(" ");
			i++;
		}
	}
	printf("\n");
}
