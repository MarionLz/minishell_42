/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:03:16 by gdaignea          #+#    #+#             */
/*   Updated: 2024/06/11 17:17:26 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_input_exit(char *input, t_data *data)
{
	int		i;
	char	**input_cpy;

	i = 0;
	if (!input)
		return (1);
	input_cpy = ft_split(input, ' ');
	if (strcmp(input_cpy[0], "exit") == 0)
	{
		while (input_cpy[i])
			i++;
		if (i > 2)
		{
			printf("exit\nminishell: exit: too many arguments\n");
			free_tab(input_cpy);
			return (g_exit_status = 1, 0);
		}
		else
		{
			printf("exit\n");
			ft_exit_and_free(input_cpy, data);
		}
	}
	free_tab(input_cpy);
	return (1);
}

void	ft_exit_and_free(char **input_cpy, t_data *data)
{
	int	i;

	if (input_cpy[1])
	{
		i = 0;
		while (input_cpy[1][i])
		{
			if (!ft_isdigit(input_cpy[1][i]))
			{
				printf("minishell: exit: %s: numeric argument required\n",
					input_cpy[1]);
				free_tab(input_cpy);
				free_tab(data->env_cpy);
				free(data);
				exit (1);
			}
			i++;
		}
	}
	free_tab(input_cpy);
	free_tab(data->env_cpy);
	free(data);
	exit(1);
}

void	actualize_status_and_exit(char *status)
{
	g_exit_status = ft_atoi(status);
	if (g_exit_status >= 0 && g_exit_status <= 255)
		exit(g_exit_status);
	else
	{
		g_exit_status %= 256;
		exit(g_exit_status);
	}
}

void	ft_exit(char **args)
{
	int	i;

	if (args[1])
	{
		i = 0;
		while (args[1][i])
		{
			if (!ft_isdigit(args[1][i]))
			{
				printf("exit\nminishell: exit: %s: numeric argument required\n",
					args[1]);
				exit (1);
			}
			i++;
		}
		actualize_status_and_exit(args[1]);
	}
	else
		exit(0);
}
