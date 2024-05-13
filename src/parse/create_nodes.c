#include "../../include/minishell.h"

/* create_exec_node : create the node of type EXEC, initialize its type, the args and end_args pointers.
exec_node->args[i]: pointer to the beginning of the command or argument.
exec_node->end_args[i]: pointer to the character following the command or argument.*/

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
	while (*start_scan < end_input && get_token(start_scan, end_input, &start_token, &end_token) == EXEC)
	{
		exec_node->args[i] = start_token;
		exec_node->end_args[i] = end_token;
		i++;
	}
	return ((t_node*)exec_node);
}
