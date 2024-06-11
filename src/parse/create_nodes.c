/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malauzie <malauzie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:47:21 by malauzie          #+#    #+#             */
/*   Updated: 2024/06/11 15:44:18 by malauzie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	fill_args(t_exec_node *exec_node, char *start_token, char *end_token,
			int *i)
{
	exec_node->args[*i] = start_token;
	exec_node->end_args[*i] = end_token;
	(*i)++;
}

t_node	*create_redir_node(int token_type, t_node *cmd, char *start_file,
			char *end_file)
{
	t_redir_node	*redir_node;

	redir_node = malloc(sizeof(*redir_node));
	if (!redir_node)
		return (NULL);
	ft_memset(redir_node, 0, sizeof(*redir_node));
	redir_node->type = REDIR;
	redir_node->r_type = token_type;
	if (token_type == HEREDOC)
		g_exit_status = -42;
	redir_node->cmd = cmd;
	redir_node->file = start_file;
	redir_node->end_file = end_file;
	init_fd_and_mode(token_type, redir_node);
	if (cmd->type == REDIR)
		return (multiple_redir(cmd, redir_node));
	return ((t_node *)redir_node);
}

t_node	*create_pipe_node(t_node *left, t_node *right)
{
	t_pipe_node	*pipe_node;

	pipe_node = malloc(sizeof(*pipe_node));
	if (!pipe_node)
		return (NULL);
	ft_memset(pipe_node, 0, sizeof(*pipe_node));
	pipe_node->type = PIPE;
	pipe_node->left = left;
	pipe_node->right = right;
	if (!pipe_node->right)
	{
		free(pipe_node->left);
		free(pipe_node);
		return (NULL);
	}
	return ((t_node *)pipe_node);
}

/* create_exec_node : create the node of type EXEC, initialize its type,
the args and end_args pointers.
exec_node->args[i]: pointer to the beginning of the command or argument.
exec_node->end_args[i]: pointer to the character following the command
or argument.*/

t_node	*create_exec_node(void)
{
	t_exec_node	*exec_node;

	exec_node = malloc(sizeof(*exec_node));
	if (!exec_node)
		return (NULL);
	ft_memset(exec_node, 0, sizeof(*exec_node));
	exec_node->type = EXEC;
	return ((t_node *)exec_node);
}
