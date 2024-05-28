#include "../../include/minishell.h"

int	run_pipe(t_node *tree, t_env *env)
{
	t_pipe_node *pipe_node;
	int			fd[2];
	pid_t		pid;
	int			status;
	int		return_status;

	return_status = 0;
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
	pid = ft_fork();
	if (pid == 0)
	{
		close (fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		run(pipe_node->right, env);
	}
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return_status = WEXITSTATUS(status);
	return (return_status) ;
}
