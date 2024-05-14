#include "../../include/minishell.h"

int	ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		perror("fork");
	return (pid);
}

void	run(t_node *tree, char **env)
{
	if (tree->type == EXEC)
		run_exec(tree, env);
	else if (tree->type == BUILTIN)
		run_builtin(tree, env);
	else if (tree->type == REDIR)
		run_redir(tree);
	else if (tree->type == PIPE)
		run_pipe(tree, env);
}
