#include "../include/minishell.h"

int	exit_status;

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

int	is_input_empty(char *input)
{
	if (!input)
	{
		printf("exit\n");
		exit (1);
	}
	if (*input == '\0')
	{
		free(input);
		return (1);
	}
	return (0);
}

void	input_handler(char *input, t_env *env)
{
	t_node *tree;

	is_input_exit(input);
	add_history(input);
	tree = parse_input(input, env);
	check_and_run(tree, env); //cot cot 🐔
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_env	*new_env;
	
	(void)av;
	if (ac > 1)
		printf("minishell: program does not require arguments");
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
		if (!is_input_empty(input))
			input_handler(input, new_env);
	}
	free(new_env);
	return (0);
}
