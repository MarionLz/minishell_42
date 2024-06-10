/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:01:26 by gdaignea          #+#    #+#             */
/*   Updated: 2024/06/10 17:03:38 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	run_builtin(char **args, t_data *data)
{
	if (ft_strncmp(args[0], "cd", 2) == 0)
		ft_cd(args, data);
	else if (ft_strncmp(args[0], "echo", 4) == 0)
		ft_echo(args);
	else if (ft_strncmp(args[0], "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(args[0], "export", 6) == 0)
		ft_export(args, data);
	else if (ft_strncmp(args[0], "unset", 5) == 0)
		ft_unset(args, data);
	else if (ft_strncmp(args[0], "exit", 4) == 0)
		ft_exit(args);
	else if (ft_strncmp(args[0], "env", 3) == 0)
		ft_env(data);
	return ;
}
