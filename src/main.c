/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malauzie <malauzie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:02:19 by gdaignea          #+#    #+#             */
/*   Updated: 2024/06/11 17:38:41 by malauzie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit_status;

void	ft_error(char *error)
{
	perror(error);
	exit(1);
}

bool	contain_only_whitespace(char *input)
{
	int	i;

	i = 0;
	while (input[i] && is_whitespace(input[i]))
		i++;
	if (i == (int)ft_strlen(input))
		return (true);
	return (false);
}

//check if input is NULL. if so, it means that readline sent back NULL 
//and that there was nothing to read. this handle the case when when ctrl+d 
//is called and exit the program. 
//check also if the 1st character of input is a null char. 
//It means that readline read something but it is an empty line
int	is_input_empty(char *input, t_data *data)
{
	if (!input)
	{
		free_tab(data->env_cpy);
		free(data);
		free(input);
		printf("exit\n");
		exit (1);
	}
	if (*input == '\0' || contain_only_whitespace(input))
	{
		free(input);
		return (1);
	}
	return (0);
}

//before anything else, check if input is exit cmd alone
//if so, exit the program.
//otherwise,, parse and execute the input
void	*input_handler(char *input, t_data *data)
{
	t_node	*tree;

	if (is_input_exit(input, data) == 0)
		return (0);
	add_history(input);
	tree = parse_input(input, data);
	if (!tree)
		return (NULL);
	if (tree != NULL)
	{
		check_and_run(tree, data);
		free_tree(tree);
		free(data->new_input);
		free(input);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_data	*data;

	(void)av;
	if (ac > 1)
	{
		printf("minishell: program does not require arguments");
		return (0);
	}
	data = handle_env(env);
	if (!env)
		return (1);
	g_exit_status = 0;
	while (1)
	{
		setup_main_signals();
		input = readline("minishell $ ");
		if (!is_input_empty(input, data))
			input_handler(input, data);
	}
	return (0);
}
