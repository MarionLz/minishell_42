#include "../../include/minishell.h"

char	*get_user_name(t_data *data)
{
	int		i;
	int		j;
	char	*path;

	i = 0;
	j = 5;
	path = ft_strdup("");
	while (data->env_cpy[i])
	{
		if (ft_strncmp("HOME=", data->env_cpy[i], 5) == 0)
			break;
		i++;
	}
	if (!data->env_cpy[i])
	{
		printf("minishell: cd: HOME not set\n");
		return (NULL);
	}
	while (data->env_cpy[i][j])
	{
		path = strjoin_char(path, data->env_cpy[i][j]);
		j++;
	}
	path = strjoin_char(path, '\0');
	return (path);
}

void	change_directory(char *path)
{
	char	*error_msg;

	if (chdir(path) == -1)
	{
		error_msg = ft_strjoin("cd:", path);
		ft_error(error_msg);
	}
}

//actualize OLDPWD and PWD variables in environment
void	actualize_env(char *directory, char *var, t_data *data)
{
	int		i;
	char	*new_oldpwd;
	int		var_len;

	i = -1;
	var_len = (int)ft_strlen(var);
	new_oldpwd = ft_strjoin(var, directory);
	while (data->env_cpy[++i])
	{
		if (ft_strncmp(var, data->env_cpy[i], var_len) == 0)
			break ;
	}
	free(data->env_cpy[i]);
	data->env_cpy[i] = ft_strdup(new_oldpwd);
	free(new_oldpwd);
}

//change directory to the given path. 
//in case of cd alone, check if HOME variable hasn't been unset.
//if so, just display proper error message.
void	ft_cd(char **args, t_data *data)
{
	char	*old_directory;
	char	*current_directory;
	char	*path;

	old_directory = NULL;
	current_directory = NULL;
	old_directory = getcwd(old_directory, 0);
	if (!args[1])
	{
		path = get_user_name(data);
		if (path == NULL)		
			return ;
		change_directory(path);
		free(path);
	}
	else
		change_directory(args[1]);
	current_directory = getcwd(current_directory, 0);
	actualize_env(old_directory, "OLDPWD=", data);
	actualize_env(current_directory, "PWD=", data);
	free(old_directory);
	free(current_directory);
}
