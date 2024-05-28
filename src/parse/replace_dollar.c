#include "../../include/minishell.h"

/*bool	find_variable_in_env(char *str, int index, t_data *data, t_dollar *var_env)
{
	int	i;

	i = 0;
	var_env->len_name = ft_strnlen(str, index, " \"");
	var_env->name = ft_strndup(str, index, var_env->len_name);
	while (data->new_env[i])
	{
		if (ft_strncmp(var_env->name, data->new_env[i], var_env->len_name) == 0 && data->new_env[i][var_env->len_name] == '=')
		{
			var_env->len_value = ft_strnlen(data->new_env[i], var_env->len_name + 1, "\0");
			var_env->value = ft_strndup(data->new_env[i], var_env->len_name + 1, var_env->len_value);
			free(var_env->name);
			return (true);
		}
		i++;
	}
	free(var_env->name);
	return (false);
}

void	replace_dollar(t_dollar *var_env, char **new_input, int *i, int *j)
{
	int	k;

	k = 0;
	while (var_env->value[k])
	{
		(*new_input)[*j] = var_env->value[k];
		(*j)++;
		k++;
	}
	*i += var_env->len_name + 1;
}

char	*make_new_input(char *input, t_dollar *var_env)
{
	int	i;
	int	j;
	char *new_input;

	i = 0;
	j = 0;
	new_input = malloc(sizeof(char) * (ft_strlen(input) - (var_env->len_name + 1) + var_env->len_value + 1));
	if (!new_input)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '$')
			replace_dollar(var_env, &new_input, &i, &j);
		else
		{
			new_input[j] = input[i];
			i++;
			j++;
		}
	}
	new_input[j] = '\0';
	free(var_env->value);
	return (new_input);
}

char	*get_exit_status(char *input, t_dollar *var_env)
{
	var_env->value = ft_itoa(g_exit_status);
	printf("exit status = %d.\n", g_exit_status);
	var_env->len_value = ft_strlen(var_env->value);
	var_env->len_name = 2;
	return (make_new_input(input, var_env));
}*/

char	*handle_dollar(char *input, char *new_input, t_env *env)
{
	int	i;
	int	simple_quote;
	int	double_quotes;
	
	(void)env;
	i = 0;
	simple_quote = 0;
	double_quotes = 0;
	while (input[i])
	{
		check_quotes(&simple_quote, &double_quotes, input, i);
		if (input[i] == '$' && (double_quotes || (!double_quotes && !simple_quote)))
		{
			/*if (input[i + 1] == '?')
				input = get_exit_status(input, var_env);*/
			/*if (find_variable_in_env(input, i + 1, new_input, new_env))
				input = make_new_input(input, var_env);*/
			printf("ok\n");
		}
		i++;
	}
	return (new_input);
}
