/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:03:21 by gdaignea          #+#    #+#             */
/*   Updated: 2024/06/11 15:03:48 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//1st char of export variable must be a alphabetical char or a '_'
//all other characters until the '=' must be alphanum char
//if not, var unvalid.
//if no '=', var unvalid.

int	is_var_valid(char *args)
{
	int	i;

	i = 0;
	if (!ft_isalpha(args[i]) && args[i] != '_')
		return (0);
	i++;
	while (args[i] != '=')
	{
		if (args[i] == '\0')
			return (0);
		if (!ft_isalnum(args[i]) && args[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

//check if the export variable name is already existing in the env
int	does_var_exist(char *var, t_data *data)
{
	char	**var_name;
	int		var_name_len;
	int		i;

	i = 0;
	var_name = ft_split(var, '=');
	var_name_len = ft_strlen(var_name[0]);
	while (data->env_cpy[i])
	{
		if (ft_strncmp(var_name[0], data->env_cpy[i], var_name_len) == 0
			&& data->env_cpy[i][var_name_len] == '=')
		{
			free_tab(var_name);
			return (1);
		}
		i++;
	}
	free_tab(var_name);
	return (0);
}

void	add_new_var(char *var, t_data *data)
{
	int		i;
	char	**new_env;

	i = 0;
	while (data->env_cpy[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return ;
	i = 0;
	while (data->env_cpy[i])
	{
		new_env[i] = ft_strdup(data->env_cpy[i]);
		i++;
	}
	new_env[i] = ft_strdup(var);
	i++;
	new_env[i] = NULL;
	free_tab(data->env_cpy);
	data->env_cpy = dup_env(new_env);
	free_tab(new_env);
}

void	change_var(char *var, t_data *data)
{
	char	**var_name;
	int		var_name_len;
	int		i;

	i = -1;
	var_name = ft_split(var, '=');
	var_name_len = ft_strlen(var_name[0]);
	while (data->env_cpy[++i])
	{
		if (ft_strncmp(var_name[0], data->env_cpy[i], var_name_len) == 0)
			break ;
	}
	free(data->env_cpy[i]);
	data->env_cpy[i] = ft_strdup(var);
	free_tab(var_name);
}

void	ft_export(char **args, t_data *data)
{
	int	i;

	i = 1;
	if (!args[i])
		printf("export: identifier needed\n");
	while (args[i])
	{
		if (is_var_valid(args[i]) == 0)
		{
			printf("export: '%s': not a valid identifier\n", args[1]);
			return ;
		}
		if (does_var_exist(args[1], data) == 0)
			add_new_var(args[i], data);
		else
			change_var(args[i], data);
		i++;
	}
}
