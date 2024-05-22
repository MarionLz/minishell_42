#include "../../include/minishell.h"

t_node	*parse_redir(t_node *node, char **start_scan, char *end_input)
{
	int		token_type;
	char	*start_file;
	char	*end_file;

	while (insight_input(start_scan, end_input, "<>"))
	{
		token_type = get_token(start_scan, end_input, 0, 0);
		if (get_token(start_scan, end_input, &start_file, &end_file) != EXEC)
			printf("error, missing file for redirection\n");
		if (token_type == IN_REDIR)
			node = create_redir_node(node, start_file, end_file, O_RDONLY, 0);
		else if (token_type == OUT_REDIR)
			node = create_redir_node(node, start_file, end_file, O_RDWR | O_CREAT | O_TRUNC, 1);
		/*else if (token_type == HEREDOC)
			node = create_redir_node();*/
		else if (token_type == APPEND)
			node = create_redir_node(node, start_file, end_file, O_RDWR | O_CREAT | O_APPEND, 1);
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
	int 		type;

	node = create_exec_node(start_scan);
	exec_node = (t_exec_node *)node;
	node = parse_redir(node, start_scan, end_input);
	i = 0;
	while (!insight_input(start_scan, end_input, "|"))
	{
		if ((type = get_token(start_scan, end_input, &start_token, &end_token)) == -1)
			break;
		exec_node->args[i] = start_token;
		printf("start token = %s\n", exec_node->args[i]);
		exec_node->end_args[i] = end_token;
		printf("end token = %s\n", exec_node->end_args[i]);
		i++;
		if (i >= MAX_ARGS)
			printf("error, too many arguments.\n");
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
		node = create_pipe_node(node, parse_pipe(start_scan, end_input));
	}
	return (node);
}

/* nulterminate : Replace the character following the command or its argument with
a NULL character to indicate the end of the string. Thus, during execution, the program
will only read until the NULL character. */
t_node	*nulterminate(t_node *tree)
{
	t_exec_node		*exec_node;
	t_redir_node	*redir_node;
	t_pipe_node		*pipe_node;
	int				i;

	if (tree->type == EXEC)
	{
		exec_node = (t_exec_node *)tree;
		i = 0;
		while (exec_node->args[i])
		{
			*exec_node->end_args[i] = 0;
			i++;
		}
	}
	if (tree->type == REDIR)
	{
		redir_node = (t_redir_node *)tree;
		nulterminate(redir_node->cmd);
		*redir_node->end_file = 0;
	}
	if (tree->type == PIPE)
	{
		pipe_node = (t_pipe_node *)tree;
		nulterminate(pipe_node->left);
		nulterminate(pipe_node->right);
	}
	return (tree);
}

t_node	*parse_input(char *input)
{
	char	*end_input;
	t_node	*tree;

	/*input = clean_input(input);
	printf("input = %s\n", input);
	if (!input)
		return (NULL);*/
	end_input = input + ft_strlen(input);
	tree = parse_pipe(&input, end_input);
	return (nulterminate(tree));
}
