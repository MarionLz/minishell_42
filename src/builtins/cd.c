# include "../../include/minishell.h"

void	actualize_env(char *directory, char *var, t_env *env)
{
	int	i;
	char *new_oldpwd;
	int	var_len;

	i = -1;
	var_len = (int)ft_strlen(var);
	new_oldpwd = ft_strjoin(var, directory);
	while (env->env_cpy[++i])
	{
		if (ft_strncmp(var, env->env_cpy[i], var_len) == 0)
			break ;
	}
	free(env->env_cpy[i]);
	env->env_cpy[i] = ft_strdup(new_oldpwd);
	free(new_oldpwd);
}

void    ft_cd(char **args, t_env *env)
{
	char *error_msg;
	char *old_directory;
	char *current_directory;

	old_directory = NULL;
	current_directory = NULL;
	old_directory = getcwd(old_directory, 0);
	if (chdir(args[1]) == -1)
	{
		error_msg = ft_strjoin("cd:", args[0]);
		ft_error(error_msg);
	}
	current_directory = getcwd(current_directory, 0);
	actualize_env(old_directory, "OLDPWD=", env);
	actualize_env(current_directory, "PWD=", env);
	free(old_directory);
	free(current_directory);
}
