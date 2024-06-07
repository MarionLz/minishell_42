#include "../../include/minishell.h"

void	run_next_node_left(t_pipe_node *pipe_node, int *fd, t_data *data)
{
	t_redir_node *rnode;

	if (pipe_node->left->type == REDIR)
	{
		rnode = (t_redir_node *) pipe_node->left;
		if (rnode->is_heredoc == true)
		{
			dup2(data->stdin_cpy, STDIN_FILENO);
			ft_heredoc(rnode);
			pipe_node->left = rnode->cmd;
		}
	}
	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
	run(pipe_node->left, data);
	exit(exit_status);
}

void	run_next_node_right(t_pipe_node *pipe_node, int *fd, t_data *data)
{
	t_redir_node *rnode;

	if (pipe_node->right->type == REDIR)
	{
		rnode = (t_redir_node *) pipe_node->right;
		if (rnode->is_heredoc == true)
		{
			dup2(data->stdin_cpy, STDIN_FILENO);
			ft_heredoc(rnode);
			pipe_node->right = rnode->cmd;
		}
	}
	else
	{
		close (fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
	}
	run(pipe_node->right, data);
	exit(exit_status);
}

int	wait_for_process(pid_t pid1/* , pid_t pid2 */)
{
	int	status;
	int	return_status;

	return_status = 0;
	waitpid(pid1, &status, 0);
	if (WIFEXITED(status))
		return_status = WEXITSTATUS(status);
	return (return_status);
}

/* one of the most important fct.
fork and set up pipes each time there is one.
then call recursivly run fct with the next left and right nodes
of the tree, as it's been parsed.
then make sure to wait child processes in the proper order and to return 
the proper exit_status so $? cmd (calls last exit_status) 
is updated all the time  */
int	run_pipe(t_node *tree, t_data *data)
{
	t_pipe_node	*pipe_node;
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
		run_next_node_left(pipe_node, fd, data);
	return_status = wait_for_process(pid1);
	pid2 = ft_fork();
	if (pid2 == 0)
		run_next_node_right(pipe_node, fd, data);
	close(fd[0]);
	close(fd[1]);
	return_status = wait_for_process(pid2);
	return (return_status);
}
