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
	return(true);
}

char **increase_shell_level(t_env *new_env)
{
	int		i;
	char	*old_level;
	char	*new_level;
	int		level;

	i = 0;
	while (new_env->env_cpy[i])
	{
		if (ft_strncmp(new_env->env_cpy[i], "SHLVL", 5) == 0 && new_env->env_cpy[i][5] == '=')
		{
			old_level = &new_env->env_cpy[i][6];
			if (!valid_num_content(old_level))
			{
				new_env->env_cpy[i] = ft_strnjoin(new_env->env_cpy[i], "0", 6);
				return (new_env->env_cpy);
			}
			level = ft_atoi(old_level) + 1;
			new_level = ft_itoa(level);
			new_env->env_cpy[i] = ft_strnjoin(new_env->env_cpy[i], new_level, 6);
			return (new_env->env_cpy);
		}
		i++;
	}
	add_new_var("SHLVL=0", new_env);
	return (new_env->env_cpy);
}

t_env	*handle_env(char **env)
{
	t_env	*new_env;

	new_env = malloc(sizeof(*new_env));
	if (!new_env)
		return (NULL);
	new_env->env_cpy = dup_env(env);
	new_env->env_cpy = increase_shell_level(new_env);
	return (new_env);
}
