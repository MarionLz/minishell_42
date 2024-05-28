#include "../../include/minishell.h"

void	run_next_node_left(t_pipe_node *pipe_node, int *fd, t_env *env)
{
	close(fd[0]);
	dup2(fd[1], 1),
	close (fd[1]);
	run(pipe_node->left, env);
	exit(exit_status);
}

void	run_next_node_right(t_pipe_node *pipe_node, int *fd, t_env *env)
{
	close (fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	run(pipe_node->right, env);
	exit(exit_status);
}

int	wait_for_process(pid_t pid1, pid_t pid2)
{
	int	status1;
	int	status2;
	int	return_status;

	return_status = 0;
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	if (WIFEXITED(status2))
		return_status = WEXITSTATUS(status2);
	return (return_status) ;
}

int	run_pipe(t_node *tree, t_env *env)
{
	t_pipe_node *pipe_node;
	int			fd[2];
	pid_t		pid1;
	pid_t		pid2;
	int			return_status;

	return_status = 0;
	pipe_node = (t_pipe_node *)tree;
	if (pipe(fd) == -1)
		ft_error("pipe");
	pid1 = ft_fork();
	if (pid1 == 0)
		run_next_node_left(pipe_node, fd, env);
	pid2 = ft_fork();
	if (pid2 == 0)
		run_next_node_right(pipe_node, fd, env);
	close(fd[0]);
	close(fd[1]);
	return_status = wait_for_process(pid1, pid2);
	return (return_status) ;
}
