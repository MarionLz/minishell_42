#include "../include/minishell.h"

void	ft_error(char *error)
{
	perror(error);
	exit(1);
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

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_node	*tree;
	t_env	*new_env;
	
	(void)ac;
	(void)av;
	new_env = malloc(sizeof(*new_env));
	if (!new_env)
		return (1);
	new_env->env_cpy  = dup_env(env);
	exit_status = 0;
	handle_sigint();
	handle_sigquit();
	while (1)
	{
		input = readline("minishell $ ");
		if (input == NULL)
		{
			printf("exit\n");
			break ;
		}
		is_input_exit(input);
		add_history(input);
		tree = parse_input(input, new_env);
		check_and_run(tree, new_env); //cot cot 🐔
	}
	free(new_env);
	return (0);
}
