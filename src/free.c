#include "../include/minishell.h"

void	free_env(t_env *env)
{
	int i;

	i = 0;
	while (env->env_cpy[i])
	{
		free(env->env_cpy[i]);
		i++;
	}
	free(env->env_cpy);
    free(env);
}

void	*free_tab_until_n(char **env, int n)
{
	int j;

	j = 0;
	while (j < n)
	{
		free(env[j]);
		j++;
	}
	free(env);
	return (NULL);
}
