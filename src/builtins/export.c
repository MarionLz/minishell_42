#include "../../include/minishell.h"

//1st char of export variable must be a alphabetical char
//all other characters until the '=' must be alphanum char
//if not, var unvalid.
//if no '=', var unvalid.

/*int	is_var_valid(char *var)
{
	int	i;

	i = 1;
	if (ft_isalpha(var[0]) == 0)
		return (0);
	while (var[i] != '=')
	{
		if (var[i] == '\0')
			return (0);
		if (ft_isalnum(var[i]) == 0)
			return(0);
		i++;
	}
	return (1);
}

//check if the export variable name is already existing in the env
int	does_var_exist(char *cmd, t_data *data)
{
	char	**var_name;
	int		var_name_len;
	int		i;

	i = 0;
	var_name = ft_split(cmd, '=');
	var_name_len = ft_strlen(var_name[0]);
	while (data->new_env[i])
	{
		if (ft_strncmp(var_name[0], data->new_env[i], var_name_len) == 0)
			return (1);
		i++;
	}
	free_tab(var_name);
	return (0);
}

void	add_new_var(char *cmd, t_data *data)
{
	int	i;
	char **cpy_env;

	i = 0;
	while (data->new_env[i])
		i++;
	cpy_env = (char **)malloc(sizeof(char *) * i + 2);
	if (!cpy_env)
		return ;
	i = 0;
	while (data->new_env[i])
	{
		cpy_env[i] = ft_strdup(data->new_env[i]);
		i++;
	}
	cpy_env[i] = ft_strdup(cmd);
	i++;
	cpy_env[i] = '\0';
	free_tab(data->new_env);
	data->new_env = dup_env(cpy_env);
	free_tab(cpy_env);
}

void	ft_export(char *cmd, t_data *data)
{
	char **split_cmd;

	split_cmd = ft_split(cmd, ' ');
	if (is_var_valid(split_cmd[1]) == 0)
	{
		printf("export: '%s': not a valid identifier\n", split_cmd[1]);
		free_tab(split_cmd);
		return ;
	}
	if (does_var_exist(split_cmd[1], data) == 0)
		add_new_var(split_cmd[1], data);
	else
		change_var(split_cmd[1], data);
	free_tab(split_cmd);
}*/
