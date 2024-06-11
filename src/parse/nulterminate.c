/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nulterminate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malauzie <malauzie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 10:13:47 by malauzie          #+#    #+#             */
/*   Updated: 2024/06/11 10:13:49 by malauzie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	nulterminate_exec_node(t_data *data, t_exec_node *exec_node)
{
	int	i;

	i = 0;
	data->nb_cmd += 1;
	while (exec_node->args[i])
	{
		*exec_node->end_args[i] = 0;
		i++;
	}
	if (is_builtin(exec_node->args[0]) == true)
		exec_node->is_builtin = true;
}

/* nulterminate : Replace the character following the command or its
argument with a NULL character to indicate the end of the string.
Thus, during execution, the program will only read until the NULL character. */
t_node	*nulterminate(t_node *tree, t_data *data)
{
	t_exec_node		*exec_node;
	t_redir_node	*redir_node;
	t_pipe_node		*pipe_node;

	data->nb_cmd = 0;
	if (tree->type == EXEC)
	{
		exec_node = (t_exec_node *)tree;
		nulterminate_exec_node(data, exec_node);
	}
	if (tree->type == REDIR)
	{
		redir_node = (t_redir_node *)tree;
		nulterminate(redir_node->cmd, data);
		*redir_node->end_file = 0;
	}
	if (tree->type == PIPE)
	{
		pipe_node = (t_pipe_node *)tree;
		nulterminate(pipe_node->left, data);
		nulterminate(pipe_node->right, data);
	}
	return (tree);
}
