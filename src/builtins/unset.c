#include "../../include/minishell.h"

bool	is_var_name_valid(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		if (!ft_isalpha(args[i][j]) && args[i][j] != '_')
		{
			printf("unset: '%s': not a valid identifier\n", args[1]);
			return (false);
		}
		while(args[i][j])
		{
			if (!ft_isalnum(args[i][j]) && args[i][j] != '_')
			{
				printf("unset: '%s': not a valid identifier\n", args[1]);
				return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
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
		free_tab_until_n(new_env, j);
		return (NULL);
	}
	return (variable_cpy);
}

void	ft_unset(char **args, t_env *env)
{
	int		i;
	int 	j;
	char	**new_env;
	
	i = 1;
	j = 0;
	if (!is_var_name_valid(args))
		return ;
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
