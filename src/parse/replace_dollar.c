#include "../../include/minishell.h"

char	*get_exit_status(char *new_input)
{
	char		*str_exit_status;

	str_exit_status = ft_itoa(exit_status);
	while (*str_exit_status)
	{
		new_input = strjoin_char(new_input, *str_exit_status);
		str_exit_status++;
	}
	//free(str_exit_status);
	return (new_input);
}

char	*get_var_name(t_dollar *var, char **input)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = *input;
	var->len_name = 0;
	while (*tmp && !is_whitespace(*tmp) && !is_quotes(*tmp) && !is_symbol(*tmp))
	{
		var->len_name++;
		tmp++;
	}
	var->name = malloc(sizeof (char) * var->len_name + 1);
	if (!var->name)
		return (NULL);
	while (i < var->len_name)
	{
		var->name[i] = **input;
		i++;
		(*input)++;
	}
	var->name[i] = '\0';
	return (var->name);
}

bool	find_var_in_env(t_dollar *var, t_env *env)
{
	int	i;

	i = 0;
	while(env->env_cpy[i])
	{
		if (ft_strncmp(var->name, env->env_cpy[i], var->len_name) == 0 && env->env_cpy[i][var->len_name] == '=')
		{
			var->index = i;
			return (true);
		}
		i++;
	}
	return (false);
}

char	*copy_var_value(t_dollar *var, char *new_input, t_env *env)
{
	int	i;

	i = 0;
	while (env->env_cpy[var->index][i] != '=')
		i++;
	i++;
	while (env->env_cpy[var->index][i])
	{
		new_input = strjoin_char(new_input, env->env_cpy[var->index][i]);
		i++;
	}
	return (new_input);
}

char	*replace_dollar(char *new_input, char **input, t_env *env)
{
	t_dollar	*var;

	(*input)++;
	if (**input == '?')
	{
		new_input = get_exit_status(new_input);
		(*input)++;
	}
	else
	{
		var = malloc(sizeof(*var));
		if (!var)
			return (NULL);
		ft_memset(var, 0, sizeof(*var));
		get_var_name(var, input);
		if (find_var_in_env(var, env))
			new_input = copy_var_value(var, new_input, env);
		free(var->name);
		free(var);
	}
	return (new_input);
}
