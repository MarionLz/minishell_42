/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malauzie <malauzie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:44:02 by malauzie          #+#    #+#             */
/*   Updated: 2024/06/11 15:51:55 by malauzie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_fd_and_mode(int token_type, t_redir_node	*redir_node)
{
	if (token_type == IN_REDIR)
	{
		redir_node->mode = O_RDONLY;
		redir_node->fd = 0;
	}
	if (token_type == OUT_REDIR)
	{
		redir_node->mode = O_RDWR | O_CREAT | O_TRUNC;
		redir_node->fd = 1;
	}
	if (token_type == APPEND)
	{
		redir_node->mode = O_RDWR | O_CREAT | O_APPEND;
		redir_node->fd = 1;
	}
}

t_node	*multiple_redir(t_node *cmd, t_redir_node *last_redir)
{
	t_redir_node	*first_redir;

	first_redir = (t_redir_node *)cmd;
	while (first_redir->cmd->type == REDIR)
		first_redir = (t_redir_node *)first_redir->cmd;
	if (first_redir->cmd->type == EXEC)
	{
		last_redir->cmd = first_redir->cmd;
		first_redir->cmd = (t_node *)last_redir;
	}
	return ((t_node *)cmd);
}
