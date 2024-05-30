#include "../../include/minishell.h"

void	run_builtin(char **args, t_env *env)
{
	if (ft_strncmp(args[0], "cd", 2) == 0)
		ft_cd(args, env);
	else if (ft_strncmp(args[0], "echo", 4) == 0)
		ft_echo(args);
	else if (ft_strncmp(args[0], "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(args[0], "export", 6) == 0)
		ft_export(args, env);
	else if (ft_strncmp(args[0], "unset", 5) == 0)
		ft_unset(args, env);
	else if (ft_strncmp(args[0], "exit", 4) == 0)
		ft_exit(args);
	else if (ft_strncmp(args[0], "env", 3) == 0)
		ft_env(env);
	return ;
}
