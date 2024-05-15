#include "../../include/minishell.h"

void	run_pipe(t_node *tree, char **env)
{
	t_pipe_node *pipe_node;
	int	fd[2];

	pipe_node = (t_pipe_node *)tree;
	if (pipe(fd) == -1)
		ft_error("pipe");
	if (ft_fork() == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1),
		close (fd[1]);
		run(pipe_node->left, env);
	}
	if (ft_fork() == 0)
	{
		close (fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		run(pipe_node->right, env);
	}
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	wait(NULL);
	return ;
}
