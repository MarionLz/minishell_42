#include "../../include/minishell.h"

/* create_exec_node : create the node of type EXEC, initialize its type, the args and end_args pointers.
exec_node->args[i]: pointer to the beginning of the command or argument.
exec_node->end_args[i]: pointer to the character following the command or argument.*/

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

t_node	*create_exec_node(char **start_scan, char *end_input)
{
	t_exec_node	*exec_node;
	int			i;
	char		*start_token;
	char		*end_token;

	i = 0;
	exec_node = malloc(sizeof(*exec_node));
	if (!exec_node)
		return (NULL);
	ft_memset(exec_node, 0, sizeof(*exec_node));
	exec_node->type = EXEC;
	while (*start_scan < end_input && !insight_input(start_scan, end_input, "|"))
	{
		get_token(start_scan, end_input, &start_token, &end_token);
		exec_node->args[i] = start_token;
		exec_node->end_args[i] = end_token;
		i++;
	}
	return ((t_node*)exec_node);
}
