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

int	is_line_delimiter(char *line, t_redir_node *redir_node)
{
	size_t	line_len;
	size_t	delimiter_len;

	if (!line)
	{
		printf("Debug: line is NULL\n");
		return (0);
	}
 	if (*line == '\0')
	{
		printf("Debug: line is empty\n");
		return (0);
	}
	line_len = ft_strlen(line);
	delimiter_len = ft_strlen(redir_node->file);
	if (ft_strncmp(line, redir_node->file, delimiter_len) == 0 
			&& (line_len == delimiter_len))
		return (1);
	else
		return (0);
}

void	handler_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
} 


void	run_heredoc(t_redir_node *redir_node)
{
	char	*line;
	int		file;

	file = open(".here_doc", O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (file < 0)
		ft_error(redir_node->file);
	while (1)
	{
		signal(SIGINT, handler_heredoc);  // Pour Ctrl+C
		signal(SIGQUIT, handler_heredoc);
		//signal(SIGINT, handler_heredoc);
		line = readline("> ");
		if (!line)
			return ;
		if (is_line_delimiter(line, redir_node))
		{
			free(line);
			close(file);
			return ;
		}
		else
		{
			ft_putstr_fd(line, file);
			ft_putchar_fd('\n', file);
			free(line);
		}
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
	{
		perror("Error duplicating file descriptor");
		ft_error("dup2 failed");
	}
	close(file);
}

void	run_redir(t_node *tree, t_env *env)
{
	t_redir_node 	*redir_node;

	redir_node = (t_redir_node *)tree;
	if (redir_node->type == OUT_REDIR || redir_node->type == APPEND)
	{
		if (close(redir_node->fd) < 0)
			ft_error("close stdin/stdout failed");
		if (open(redir_node->file, redir_node->mode, 0777) < 0)
			ft_error(redir_node->file);
	}
	else if (redir_node->is_heredoc == true)
		ft_heredoc(redir_node);
	else
	{
		if (close(redir_node->fd) < 0)
			ft_error("close stdin/stdout failed");
		if (open(redir_node->file, redir_node->mode, 0777) < 0)
			ft_error(redir_node->file);
	}
	run(redir_node->cmd, env);
	if (close(redir_node->fd) < 0)
		ft_error("close file failed");
	reopen_stdin_stdout(redir_node->fd);
	return ;
}
