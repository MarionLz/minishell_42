#include "../../include/minishell.h"

/* create_exec_node : create the node of type EXEC, initialize its type, the args and end_args pointers.
exec_node->args[i]: pointer to the beginning of the command or argument.
exec_node->end_args[i]: pointer to the character following the command or argument.*/

t_node	*create_redir_node(t_node *cmd, char *start_file, char *end_file, int mode, int fd)
{
	t_redir_node	*redir_node;

	redir_node = malloc(sizeof(*redir_node));
	if (!redir_node)
		return (NULL);
	ft_memset(redir_node, 0, sizeof(*redir_node));
	redir_node->type = REDIR;
	redir_node->cmd = cmd;
	redir_node->file = start_file;
	redir_node->end_file = end_file;
	redir_node->mode = mode;
	redir_node->fd = fd;
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
	return ((t_node *)pipe_node);
}

t_node	*create_exec_node()
{
	t_exec_node	*exec_node;

	exec_node = malloc(sizeof(*exec_node));
	if (!exec_node)
		return (NULL);
	ft_memset(exec_node, 0, sizeof(*exec_node));
	exec_node->type = EXEC;
	return ((t_node*)exec_node);
}
