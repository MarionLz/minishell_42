#include "../../include/minishell.h"

t_node	*parse_exec(char **start_scan, char *end_input)
{
	t_node	*node;

	node = create_exec_node(start_scan, end_input);
	return (node);
}

t_node	*parse_pipe(char **start_scan, char *end_input)
{
	t_node	*node;

	node = parse_exec(start_scan, end_input);
	if (insight_input(start_scan, end_input, "|"))
	{
		get_token(start_scan, end_input, 0, 0);
		node = create_pipe_node(node, );
	}
	return (node);
}

/* nulterminate : Replace the character following the command or its argument with
a NULL character to indicate the end of the string. Thus, during execution, the program
will only read until the NULL character. */

t_node	*nulterminate(t_node *tree)
{
	t_exec_node	*ex_node;
	int			i;

	if (tree->type == EXEC)
	{
		ex_node = (t_exec_node *)tree;
		i = 0;
		while (ex_node->args[i])
		{
			*ex_node->end_args[i] = 0;
			i++;
		}
	}
	return (tree);
}

t_node	*parse_input(char *input)
{
	char	*end_input;
	t_node	*tree;

	end_input = input + ft_strlen(input);
	tree = parse_pipe(&input, end_input);
	return (nulterminate(tree));
}