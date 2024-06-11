/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 10:14:19 by malauzie          #+#    #+#             */
/*   Updated: 2024/06/11 12:14:17 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*get_exit_status : retrieves the exit status returned by the previous
command line and replaces $? with its value.*/

char	*get_exit_status(char *new_input)
{
	char	*str_exit_status;
	int		i;

	i = 0;
	str_exit_status = ft_itoa(g_exit_status);
	while (str_exit_status[i])
	{
		new_input = strjoin_char(new_input, str_exit_status[i]);
		i++;
	}
	free(str_exit_status);
	return (new_input);
}

/*get_var_name : stores in a string the name of the environment variable
contained in the input (after the $) and calculates its length.*/

char	*get_var_name(t_dollar *var, char **input)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = *input;
	var->len_name = 0;
	while (*tmp && !is_whitespace(*tmp) && !is_quotes(*tmp)
		&& !is_symbol(*tmp) && *tmp != '$')
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

/*find_var_in_env : browses the environment to find the requested variable
in the input. Return true if it founds it, return false if not.*/

bool	find_var_in_env(t_dollar *var, t_data *data)
{
	int	i;

	i = 0;
	while (data->env_cpy[i])
	{
		if (ft_strncmp(var->name, data->env_cpy[i], var->len_name) == 0
			&& data->env_cpy[i][var->len_name] == '=')
		{
			var->index = i;
			return (true);
		}
		i++;
	}
	return (false);
}

/*copy_var_value : copies the content of the environment variable (after =)
dans new_input.*/

char	*copy_var_value(t_dollar *var, char *new_input, t_data *data)
{
	int	i;

	i = 0;
	while (data->env_cpy[var->index][i] != '=')
		i++;
	i++;
	while (data->env_cpy[var->index][i])
	{
		new_input = strjoin_char(new_input, data->env_cpy[var->index][i]);
		i++;
	}
	return (new_input);
}

/*replace_dollar : replaces the environment variable with its content.*/

char	*replace_dollar(char *new_input, char **input, t_data *data)
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
		if (find_var_in_env(var, data))
			new_input = copy_var_value(var, new_input, data);
		free(var->name);
		free(var);
	}
	return (new_input);
}
