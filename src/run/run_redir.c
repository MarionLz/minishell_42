/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malauzie <malauzie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:01:52 by gdaignea          #+#    #+#             */
/*   Updated: 2024/06/11 17:23:51 by malauzie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	reopen_stdin_stdout(int fd)
{
	if (fd == 0)
	{
		if (open("/dev/tty", O_RDONLY) < 0)
			ft_error("open stdin failed");
	}
	else if (fd == 1)
	{
		if (open("/dev/tty", O_WRONLY) < 0)
			ft_error("open stdout failed");
	}
}

//classic here_doc implementation.
//change ctrl+c and ctrl+d signals cause they don't behave 
//the same when in a here_doc prompt
//ctrl+c exit the here_doc prompt
//ctrl+d terminate the text entry like if delimiter was written.
void	run_heredoc(t_redir_node *redir_node)
{
	char	*line;
	int		file;

	file = open(".here_doc", O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (file < 0)
		ft_error(redir_node->file);
	setup_heredoc_signals();
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("minishell: warning: here-document delimited by\
			end-of-file (wanted %s)\n", redir_node->file);
			return ;
		}
		if (is_line_delimiter(line, redir_node))
		{
			free(line);
			close(file);
			return ;
		}
		else
			handle_line(line, file);
	}
}

void	ft_heredoc(t_redir_node *redir_node)
{
	int	file;

	file = 0;
	run_heredoc(redir_node);
	file = open(".here_doc", O_RDONLY, 0777);
	if (file < 0)
		ft_error("heredoc");
	if (dup2(file, 0) < 0)
		ft_error("dup2");
	close(file);
}

//check what kind of redirection has to be handled.
//if IN_REDIR or OUT_REDIR, close the proper fd (stdin or stdout basicaly)
//and open the given file (open fct attribute to the opened file
//the 1st closed fd in the list)
//if HERE_DOC, run ft_heredoc just above.
//make sure in the end to reopen stdin and stdout properly for the next input.
void	run_redir(t_node *tree, t_data *data)
{
	t_redir_node	*redir_node;

	redir_node = (t_redir_node *)tree;
	if (redir_node->r_type == HEREDOC)
	{
		dup2(data->stdin_cpy, STDIN_FILENO);
		ft_heredoc(redir_node);
	}
	else
	{
		if (close(redir_node->fd) < 0)
			ft_error("close stdin/stdout failed");
		if (open(redir_node->file, redir_node->mode, 0777) < 0)
			ft_error(redir_node->file);
	}
	run(redir_node->cmd, data);
	reopen_stdin_stdout(redir_node->fd);
	return ;
}
