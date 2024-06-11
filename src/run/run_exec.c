/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:01:35 by gdaignea          #+#    #+#             */
/*   Updated: 2024/06/11 19:11:35 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	if (!tab)
		return ;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

char	*extract_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
			return (env[i] + 5);
	}
	return (NULL);
}

char	*get_path(char *cmd, t_data *data)
{
	int		i;
	char	**allpaths;
	char	*goodpath;
	char	*subpath;
	char	*paths;

	paths = extract_env(data->env_cpy);
	if (!paths)
		return (NULL);
	allpaths = ft_split(paths, ':');
	i = -1;
	while (allpaths[++i])
	{
		subpath = ft_strjoin(allpaths[i], "/");
		goodpath = ft_strjoin(subpath, cmd);
		free(subpath);
		if (access(goodpath, F_OK | X_OK) == 0)
		{
			free_tab(allpaths);
			return (goodpath);
		}
		free(goodpath);
	}
	free_tab(allpaths);
	return (NULL);
}

void	run_exec(t_node *tree, t_data *data)
{
	t_exec_node	*exec_node;
	char		*path;

	exec_node = (t_exec_node *)tree;
	if (exec_node->is_builtin == true)
	{
		run_builtin(exec_node->args, data);
	}
	else
	{
		path = get_path(exec_node->args[0], data);
		if (execve(exec_node->args[0], exec_node->args, data->env_cpy) == -1)
		{
			if (execve(path, exec_node->args,
					data->env_cpy) == -1)
			{
				free(path);
				ft_error(exec_node->args[0]);
				exit(1);
			}
		}
	}
}
