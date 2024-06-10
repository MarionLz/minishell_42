/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:02:07 by gdaignea          #+#    #+#             */
/*   Updated: 2024/06/10 17:03:38 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	**dup_env(char **env)
{
	char	**new_env;
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (env[++i])
		;
	new_env = malloc((i + 1) * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = -1;
	while (env[++i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			while (++j < i)
				free(new_env[j]);
			free(new_env);
			return (NULL);
		}
	}
	new_env[i] = NULL;
	return (new_env);
}

bool	valid_num_content(char *str)
{
	while (*str)
	{
		if (ft_isalpha(*str))
			return (false);
		str++;
	}
	return (true);
}

char	**increase_shell_level(t_data *data)
{
	int		i;
	char	*old_level;
	char	*new_level;
	int		level;

	i = -1;
	while (data->env_cpy[++i])
	{
		if (ft_strncmp(data->env_cpy[i], "SHLVL", 5) == 0
			&& data->env_cpy[i][5] == '=')
		{
			old_level = &data->env_cpy[i][6];
			if (!valid_num_content(old_level))
			{
				data->env_cpy[i] = ft_strnjoin(data->env_cpy[i], "0", 6);
				return (data->env_cpy);
			}
			level = ft_atoi(old_level) + 1;
			new_level = ft_itoa(level);
			data->env_cpy[i] = ft_strnjoin(data->env_cpy[i], new_level, 6);
			return (data->env_cpy);
		}
	}
	add_new_var("SHLVL=0", data);
	return (data->env_cpy);
}

t_data	*handle_env(char **env)
{
	t_data	*data;

	data = malloc(sizeof(*data));
	if (!data)
		return (NULL);
	data->env_cpy = dup_env(env);
	data->env_cpy = increase_shell_level(data);
	data->stdout_cpy = dup(STDOUT_FILENO);
	data->stdin_cpy = dup(STDIN_FILENO);
	return (data);
}
