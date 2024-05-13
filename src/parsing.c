#include "../include/minishell.h"

bool	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
		return (true);
	return (false);
}

bool	is_symbol(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

int	insight_input(char **start_token, char *end_input, char *target)
{
	char *str;

	str = *start_token;
	while (str < end_input && is_whitespace(*str))
		str++;
	*start_token = str;
	return (*str && ft_strchr(target, *str));
}

void	get_type(char **str, int *type, char *end_input)
{
	if (**str == '|')
	{
		*type = PIPE;
		(*str)++;
	}
	else if (**str == '<')
	{
		if (**str++ == '<')
			*type = HEREDOC;
		else
			*type = IN_REDIR;
	}
	else if (**str == '>')
	{
		if (**str++ == '>')
			*type = APPEND;
		else
			*type = OUT_REDIR;
	}
	else
	{
		*type = (EXEC);
		while (*str < end_input && !is_whitespace(**str) && !is_symbol(**str))
			(*str)++;
	}
}

int	get_token(char **start_scan, char *end_input, char **start_token, char **end_token)
{
	char	*str;
	int		type;

	str = *start_scan;
	while (str < end_input && is_whitespace(*str))
		str++;
	*start_token = str;
	if (!str)
		type = -1;
	get_type(&str, &type, end_input);
	*end_token = str;
	while (str < end_input && is_whitespace(*str))
		str++;
	*start_scan = str;
	return (type);
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
	while (*start_scan < end_input && get_token(start_scan, end_input, &start_token, &end_token) == EXEC)
	{
		printf("start = %s\n", *start_scan);
		exec_node->args[i] = start_token;
		exec_node->end_args[i] = end_token;
		printf("args[%d] = %s\n", i, exec_node->args[i]);
		printf("end_args[0] = %s\n", exec_node->end_args[i]);
		i++;
	}
	return ((t_node*)exec_node);
}

t_node	*parse_exec(char **start_scan, char *end_input)
{
	t_node	*node;

	node = create_exec_node(start_scan, end_input);
	return (node);
}

t_node	*parse_input(char *input)
{
	char	*end_input;
	t_node	*tree;

	end_input = input + ft_strlen(input);
	tree = parse_exec(&input, end_input);
	replace_whitespaces();
	nulterminate pour remplacer tous les espaces par des \0
	return (tree);
}