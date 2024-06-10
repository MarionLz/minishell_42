/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:02:13 by gdaignea          #+#    #+#             */
/*   Updated: 2024/06/10 17:03:38 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env_cpy[i])
	{
		free(data->env_cpy[i]);
		i++;
	}
	free(data->env_cpy);
}

void	free_tree(t_node *tree)
{
	t_pipe_node		*pipe_node;
	t_redir_node	*redir_node;
	t_exec_node		*exec_node;

	if (tree->type == EXEC)
	{
		exec_node = (t_exec_node *)tree;
		free(exec_node);
	}
	else if (tree->type == REDIR)
	{
		redir_node = (t_redir_node *)tree;
		free_tree(redir_node->cmd);
		free(redir_node);
	}
	else if (tree->type == PIPE)
	{
		pipe_node = (t_pipe_node *)tree;
		free_tree(pipe_node->left);
		free_tree(pipe_node->right);
		free(pipe_node);
	}
}

void	*free_tab_until_n(char **env, int n)
{
	int	j;

	j = 0;
	while (j < n)
	{
		free(env[j]);
		j++;
	}
	free(env);
	return (NULL);
}
