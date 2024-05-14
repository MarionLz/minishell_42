# include "../../include/minishell.h"


//A voir pour le cas de $=xxxxx
void	ft_echo(char **args)
{
	if (ft_strncmp(args[1], "-n", 2) == 0)
		printf("%s", args[2]);
	else
		printf("%s\n", args[1]);
}
