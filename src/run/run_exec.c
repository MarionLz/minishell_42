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

char	*get_path(char *cmd, t_env *env)
{
	int		i;
	char	**allpaths;
	char	*goodpath;
	char	*subpath;

	allpaths = ft_split(extract_env(env->env_cpy), ':');
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

void	run_exec(t_node *tree, t_env *env)
{
	t_exec_node *ex_node;
	char *path;

	ex_node = (t_exec_node *)tree;
	/*if (ex_node->args[0] == 0)
		exit ();*/
	if (ex_node->is_builtin == true)
		run_builtin(ex_node->args, env);
	path = get_path(ex_node->args[0], env);
	if (execve(path, ex_node->args, env->env_cpy) == -1)
	{
		free(path);
		ft_error(ex_node->args[0]);
		exit(1);
	}
}