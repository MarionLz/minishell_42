/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:03:07 by gdaignea          #+#    #+#             */
/*   Updated: 2024/06/10 17:03:38 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_empty_quotes(char *str)
{
	char	quote;

	if (is_quotes(*str))
	{
		quote = *str;
		str++;
		if (*str == quote)
			return (true);
	}
	return (false);
}

void	print_args(char **args, int i)
{
	while (args[i])
	{
		if (!is_empty_quotes(args[i]))
			printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
}

void	ft_echo(char **args)
{
	int	i;

	if (args[1] && compare_cmd(args[1], "-n", 2) == 0)
	{
		i = 2;
		print_args(args, i);
	}
	else
	{
		i = 1;
		print_args(args, i);
		printf("\n");
	}
}
