#include "../../include/minishell.h"

void	error_unset(char **tab, int i)
{
	int	j;

	j = 0;
	printf("unset : %s : invalid parameter name\n", tab[i]);
	while (tab[j])
	{
		free(tab[j]);
		j++;
	}
	free(tab);
	exit (EXIT_FAILURE);
}

void	check_var_name(char **tab)
{
	int	i;
	int	j;

	i = 1;
	while (tab[i])
	{
		j = 0;
		if (!ft_isalpha(tab[i][j]) && tab[i][j] != '_')
			error_unset(tab, i);
		while(tab[i][j])
		{
			if (!ft_isalnum(tab[i][j]) && tab[i][j] != '_')
				error_unset(tab, i);
			j++;
		}
		i++;
	}
}

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	*free_env(char **env, int i)
{
	int j;

	j = 0;
	while (j < i)
	{
		free(env[j]);
		j++;
	}
	free(env);
	return (NULL);
}

int	find_var_to_delete(char *env, char **split_cmd)
{
	int		j;
	int		len_var;

	j = 1;
	while (split_cmd[j])
	{
		len_var = ft_strlen(split_cmd[j]);
		if (ft_strncmp(env, split_cmd[j], len_var) == 0 && env[len_var] == '=')
			return (1);
		j++;
	}
	return (0);
}

char	**unset(char *cmd, t_data *data)
{
	int		i;
	int 	j;
	char	**env_copy;
	char	**split_cmd;
	
	i = 0;
	j = 0;
	split_cmd = ft_split(cmd, ' ');
	check_var_name(split_cmd);
	env_copy = malloc((tab_len(data->new_env) - (tab_len(split_cmd) - 1) + 1) * sizeof(char *));
	if (!env_copy)
		return (NULL);
	while (data->new_env[i])
	{
		if (find_var_to_delete(data->new_env[i], split_cmd) == 0)
		{
			env_copy[j] = ft_strdup(data->new_env[i]);
			if (!env_copy[j])
				return (free_env(env_copy, j));
			j++;
		}
		i++;
	}
	env_copy[j] = NULL;
	free_env(data->new_env, tab_len(data->new_env));
	free_env(split_cmd, tab_len(split_cmd));
	return (env_copy);
}
