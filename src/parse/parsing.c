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
		{
			printf("error, missing file or delimiter for redirection\n");
			//exit;
		}
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
	int 		type;

	node = create_exec_node();
	exec_node = (t_exec_node *)node;
	node = parse_redir(node, start_scan, end_input);
	i = 0;
	while (!insight_input(start_scan, end_input, "|"))
	{
		if ((type = get_token(start_scan, end_input, &start_token, &end_token)) == -1)
			break;
		exec_node->args[i] = start_token;
		exec_node->end_args[i] = end_token;
		if (is_builtin(start_token) == true)
			exec_node->is_builtin = true;
		i++;
		if (i >= MAX_ARGS)
		{
			printf("error, too many arguments.\n");
			//exit(EXIT_FAILURE);
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
		node = create_pipe_node(node, parse_pipe(start_scan, end_input));
	}
	return (node);
}

/* nulterminate : Replace the character following the command or its argument with
a NULL character to indicate the end of the string. Thus, during execution, the program
will only read until the NULL character. */
t_node	*nulterminate(t_node *tree, t_env *env)
{
	t_exec_node		*exec_node;
	t_redir_node	*redir_node;
	t_pipe_node		*pipe_node;
	int				i;

	env->nb_cmd = 0;
	if (tree->type == EXEC)
	{
		exec_node = (t_exec_node *)tree;
		i = 0;
		env->nb_cmd += 1;
		while (exec_node->args[i])
		{
			*exec_node->end_args[i] = 0;
			i++;
		}
	}
	if (tree->type == REDIR)
	{
		redir_node = (t_redir_node *)tree;
		nulterminate(redir_node->cmd, env);
		*redir_node->end_file = 0;
	}
	if (tree->type == PIPE)
	{
		pipe_node = (t_pipe_node *)tree;
		nulterminate(pipe_node->left, env);
		nulterminate(pipe_node->right, env);
	}
	return (tree);
}

t_node	*parse_input(char *input, t_env *env)
{
	char	*end_input;
	t_node	*tree;

	input = clean_input(input, env);
	if (!input)
		return (NULL);
	end_input = input + ft_strlen(input);
	tree = parse_pipe(&input, end_input);
	tree = nulterminate(tree, env);
	//free(input);
	return (tree);
}
