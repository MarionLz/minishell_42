#include "../../include/minishell.h"

void	run_builtin(char **args, char **env)
{
	if (ft_strncmp(args[0], "cd", 2) == 0)
		ft_cd(args[0]);
	else if (ft_strncmp(args[0], "echo", 4) == 0)
		ft_echo(args, fd);
	else if (ft_strncmp(args[0], "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(args[0], "exit", 4) == 0)
		ft_exit();
	else if (ft_strncmp(args[0], "env", 3) == 0)
		ft_env(env);
	return ;
}