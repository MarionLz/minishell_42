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

void	*free_env_until_i(char **env, int i)
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

int	find_var_to_delete(char *env, char **args)
{
	int		j;
	int		len_var;

	j = 1;
	while (args[j])
	{
		len_var = ft_strlen(args[j]);
		if (ft_strncmp(env, args[j], len_var) == 0 && env[len_var] == '=')
			return (1);
		j++;
	}
	return (0);
}

char	*copy_variable(char *to_copy, char **new_env, int j)
{
	char *variable_cpy;

	variable_cpy = ft_strdup(to_copy);
	if (!variable_cpy)
	{
		free_env_until_i(new_env, j);
		return (NULL);
	}
	return (variable_cpy);
}

void	ft_unset(char **args, t_env *env)
{
	int		i;
	int 	j;
	char	**new_env;
	
	i = 0;
	j = 0;
	check_var_name(args);
	new_env = malloc((tab_len(env->env_cpy) - (tab_len(args) - 1) + 1) * sizeof(char *));
	if (!new_env)
		return ;
	while (env->env_cpy[i])
	{
		if (find_var_to_delete(env->env_cpy[i], args) == 0)
		{
			new_env[j] = copy_variable(env->env_cpy[i], new_env, j);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	free_tab(env->env_cpy);
	env->env_cpy = dup_env(new_env);
	return ;
}
