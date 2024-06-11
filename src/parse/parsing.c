/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 10:14:03 by malauzie          #+#    #+#             */
/*   Updated: 2024/06/11 14:33:27 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_node	*parse_error(char *message)
{
	printf("Minishell: Error: %s.\n", message);
	return (NULL);
}

t_node	*parse_redir(t_node *node, char **start_scan, char *end_input,
			t_data *data)
{
	int		token_type;
	char	*start_file;
	char	*end_file;

	(void) data;
	while (insight_input(start_scan, end_input, "<>"))
	{
		token_type = get_token(start_scan, end_input, 0, 0);
		if (get_token(start_scan, end_input, &start_file, &end_file) != EXEC)
		{
			free(node);
			return (parse_error("missing file or delimiter for redirection"));
		}
		node = create_redir_node(token_type, node, start_file, end_file);
	}
	return (node);
}

t_node	*parse_exec(char **start_scan, char *end_input, t_data *data)
{
	t_node		*node;
	t_exec_node	*exec_node;
	int			i;
	char		*start_token;
	char		*end_token;

	node = create_exec_node();
	exec_node = (t_exec_node *)node;
	node = parse_redir(node, start_scan, end_input, data);
	if (!node)
		return (NULL);
	i = 0;
	while (!insight_input(start_scan, end_input, "|"))
	{
		if ((get_token(start_scan, end_input, &start_token, &end_token)) == -1)
			break ;
		fill_args(exec_node, start_token, end_token, &i);
		if (i >= MAX_ARGS)
			return (parse_error("too many arguments"));
		node = parse_redir(node, start_scan, end_input, data);
		if (!node)
			return (NULL);
	}
	return (node);
}

t_node	*parse_pipe(char **start_scan, char *end_input, t_data *data)
{
	t_node	*node;

	node = parse_exec(start_scan, end_input, data);
	if (!node)
		return (NULL);
	if (insight_input(start_scan, end_input, "|"))
	{
		get_token(start_scan, end_input, 0, 0);
		if (check_next_token(*start_scan, end_input) == 1)
		{
			free(node);
			return (NULL);
		}
		node = create_pipe_node(node, parse_pipe(start_scan, end_input, data));
		if (!node)
		{
			free(node);
			return (NULL);
		}
	}
	return (node);
}

t_node	*parse_input(char *input, t_data *data)
{
	char	*end_input;
	char	*input_tmp;
	t_node	*tree;

	input_tmp = clean_input(input, data);
	if (!input_tmp)
		return (NULL);
	data->new_input = input_tmp;
	end_input = input_tmp + ft_strlen(input_tmp);
	tree = parse_pipe(&input_tmp, end_input, data);
	if (!tree)
	{
		free(input);
		free(data->new_input);
		return (NULL);
	}
	tree = nulterminate(tree, data);
	return (tree);
}
