/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:01:44 by gdaignea          #+#    #+#             */
/*   Updated: 2024/06/11 18:38:13 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	run_next_node_left(t_pipe_node *pipe_node, int *fd, t_data *data)
{
	t_redir_node	*rnode;

	if (pipe_node->left->type == REDIR)
	{
		rnode = (t_redir_node *) pipe_node->left;
		if (rnode->r_type == HEREDOC)
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
	exit(g_exit_status);
}

void	run_next_node_right(t_pipe_node *pipe_node, int *fd, t_data *data)
{
	t_redir_node	*rnode;

	if (pipe_node->right->type == REDIR)
	{
		rnode = (t_redir_node *) pipe_node->right;
		if (rnode->r_type == HEREDOC)
		{
			dup2(data->stdin_cpy, STDIN_FILENO);
			ft_heredoc(rnode);
			pipe_node->right = rnode->cmd;
		}
		else
			dup_right(fd);
	}
	else
		dup_right(fd);
	run(pipe_node->right, data);
	exit(g_exit_status);
}

int	wait_for_process(pid_t pid1)
{
	int	status;
	int	return_status;

	return_status = 0;
	waitpid(pid1, &status, 0);
	if (WIFEXITED(status))
		return_status = WEXITSTATUS(status);
	return (return_status);
}

int	is_there_heredoc(t_node *node)
{
	t_redir_node	*redir_node;

	if (node->type == EXEC)
		return (1);
	else
	{
		redir_node = (t_redir_node *)node;
		while (redir_node->r_type == HEREDOC)
		{
			if (redir_node->cmd->type == EXEC)
				return (1);
			redir_node = (t_redir_node *) redir_node->cmd;
		}
		if (redir_node->r_type == HEREDOC)
			return (0);
	}
	return (1);
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
	if (is_there_heredoc(pipe_node->left) == 0
		|| pipe_node->right->type == REDIR)
		return_status = wait_for_process(pid1);
	pid2 = ft_fork();
	if (pid2 == 0)
		run_next_node_right(pipe_node, fd, data);
	close(fd[0]);
	close(fd[1]);
	return_status = wait_for_process(pid1);
	return_status = wait_for_process(pid2);
	return (return_status);
}
