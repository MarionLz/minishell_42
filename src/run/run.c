#include "../../include/minishell.h"

int	ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		ft_error("fork");
	return (pid);
}

void	run(t_node *tree, t_env *env)
{
	if (tree->type == EXEC)
		run_exec(tree, env);
	else if (tree->type == REDIR)
		run_redir(tree, env);
	else if (tree->type == PIPE)
		run_pipe(tree, env);
	exit (0);
}
