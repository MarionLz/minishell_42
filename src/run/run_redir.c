#include "../../include/minishell.h"

void	run_redir(t_node *tree, char **env)
{
	t_redir_node *redir_node;

	redir_node = (t_redir_node *)tree;
	close(redir_node->fd);
	if (open(redir_node->file, redir_node->mode) < 0)
		ft_error(redir_node->file);
	run(tree, env);
	return ;
}