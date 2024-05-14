#include "../include/minishell.h"

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
	char	**env_cpy;
	t_node	*tree;

	(void)ac;
	(void)av;
	env_cpy = dup_env(env);
	while (1)
	{
		input = readline("minishell > ");
		if (input == NULL)
			return (1);
		tree = parse_input(input);
		if (ft_fork() == 0)
			run(tree, env_cpy);
		wait(NULL);
	}
}
