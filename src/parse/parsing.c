#include "../../include/minishell.h"

void	parse_error(char *message)
{
	printf("Error, %s.\n", message);
	exit (EXIT_FAILURE);
}

t_node	*parse_redir(t_node *node, char **start_scan, char *end_input)
{
	int		token_type;
	char	*start_file;
	char	*end_file;

	while (insight_input(start_scan, end_input, "<>"))
	{
		token_type = get_token(start_scan, end_input, 0, 0);
		if (get_token(start_scan, end_input, &start_file, &end_file) != EXEC)
			parse_error("missing file or delimiter for redirection");
		node = create_redir_node(token_type, node, start_file, end_file);
	}
	return (node);
}

t_node	*parse_exec(char **start_scan, char *end_input)
{
	t_node		*node;
	t_exec_node	*exec_node;
	int			i;
	char		*start_token;
	char		*end_token;

	node = create_exec_node();
	exec_node = (t_exec_node *)node;
	node = parse_redir(node, start_scan, end_input);
	i = 0;
	while (!insight_input(start_scan, end_input, "|"))
	{
		if ((get_token(start_scan, end_input, &start_token, &end_token)) == -1)
			break;
		exec_node->args[i] = start_token;
		exec_node->end_args[i] = end_token;
		i++;
		if (i >= MAX_ARGS)
		{
			parse_error("too many arguments");
		}
		node = parse_redir(node, start_scan, end_input);
	}
	return (node);
}

t_node	*parse_pipe(char **start_scan, char *end_input)
{
	t_node	*node;

	node = parse_exec(start_scan, end_input);
	if (insight_input(start_scan, end_input, "|"))
	{
		get_token(start_scan, end_input, 0, 0);
		if (check_for_double_pipe(*start_scan, end_input) == 1)
			parse_error("double pipe");
		node = create_pipe_node(node, parse_pipe(start_scan, end_input));
	}
	return (node);
}

t_node	*parse_input(char *input, t_data *data)
{
	char	*end_input;
	char	*input_tmp;
	t_node	*tree;

	input_tmp = clean_input(input, data);
	data->new_input = input_tmp;
	if (!input)
		return (NULL);
	end_input = input_tmp + ft_strlen(input_tmp);
	tree = parse_pipe(&input_tmp, end_input);
	tree = nulterminate(tree, data);
	return (tree);
}
