# include "../../include/minishell.h"

void    ft_cd(char **args)
{
	if (chdir(args[1]) == -1)
		perror("cd");
}