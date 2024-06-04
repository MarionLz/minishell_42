#include "../../include/minishell.h"

//1st char of export variable must be a alphabetical char or a '_'
//all other characters until the '=' must be alphanum char
//if not, var unvalid.
//if no '=', var unvalid.

int	is_var_valid(char *args)
{
	int	i;

	i = 1;
	if (!ft_isalpha(args[i]) && args[i] != '_')
		return (0);
	while(args[i] != '=')
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
int	does_var_exist(char *var, t_env *env)
{
	char	**var_name;
	int		var_name_len;
	int		i;

	i = 0;
	var_name = ft_split(var, '=');
	var_name_len = ft_strlen(var_name[0]);
	while (env->env_cpy[i])
	{
		if (ft_strncmp(var_name[0], env->env_cpy[i], var_name_len) == 0 && env->env_cpy[i][var_name_len] == '=')
			return (1);
		i++;
	}
	free_tab(var_name);
	return (0);
}

void	add_new_var(char *var, t_env *env)
{
	int	i;
	char **new_env;

	i = 0;
	while (env->env_cpy[i])
		i++;
	new_env = (char **)malloc((sizeof(char *) * i) + 2);
	if (!new_env)
		return ;
	i = 0;
	while (env->env_cpy[i])
	{
		new_env[i] = ft_strdup(env->env_cpy[i]);
		i++;
	}
	new_env[i] = ft_strdup(var);
	i++;
	new_env[i] = NULL;
	free_tab(env->env_cpy);
	env->env_cpy = dup_env(new_env);
}

void	change_var(char *var, t_env *env)
{
	char **var_name;
	int	var_name_len;
	int	i;

	i = -1;
	var_name = ft_split(var, '=');
	var_name_len = ft_strlen(var_name[0]);
	while (env->env_cpy[++i])
	{
		if (ft_strncmp(var_name[0], env->env_cpy[i], var_name_len) == 0)
			break ;
	}
	free(env->env_cpy[i]);
	env->env_cpy[i] = ft_strdup(var);
	free_tab(var_name);
}

void	ft_export(char **args, t_env *env)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (is_var_valid(args[i]) == 0)
		{
			printf("export: '%s': not a valid identifier\n", args[1]);
			return ;
		}
		if (does_var_exist(args[1], env) == 0)
			add_new_var(args[i], env);
		else
			change_var(args[i], env);
		i++;
	}
}
