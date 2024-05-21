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

void	run_redir(t_node *tree, t_env *env)
{
	t_redir_node *redir_node;

	redir_node = (t_redir_node *)tree;
	if (close(redir_node->fd) < 0)
		ft_error("close stdin/stdout failed");
	if (redir_node->type == OUT_REDIR || redir_node->type == APPEND)
	{
		if (open(redir_node->file, redir_node->mode, 0666) < 0)
			ft_error("open file failed");
	}
	else
		if (open(redir_node->file, redir_node->mode) < 0)
			ft_error("open file failed");
	run(redir_node->cmd, env);
	if (close(redir_node->fd) < 0)
		ft_error("close file failed");
	reopen_stdin_stdout(redir_node->fd);
	return ;
}
