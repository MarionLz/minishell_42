#include "../../include/minishell.h"

//fonctions de free a ajouter
void	is_input_exit(char *input)
{
	int	i;
	char **input_cpy;

	i = 0;
	input_cpy = ft_split(input, ' ');
	if (strcmp(input_cpy[0], "exit") == 0)
	{
		while (input_cpy[i])
			i++;
		if (i > 2)
		{
			printf("exit\nminishell: exit: too many arguments\n");
			free_tab(input_cpy);
			return ;
		}
		else
		{
			printf("exit\n");
			ft_exit_and_free(input_cpy);
		}
	}
	return ;
}

void	ft_exit_and_free(char **input_cpy)
{
	int	i;

	if (input_cpy[1])
	{
		i = 0;
		while (input_cpy[1][i])
		{
			if (!ft_isdigit(input_cpy[1][i]))
			{
				printf("exit\nminishell: exit: %s: numeric argument required\n", input_cpy[1]);
				free_tab(input_cpy);
				exit (1);
			}
			i++;
		}
	}
	free_tab(input_cpy);
	exit(1);
}

void	actualize_status_and_exit(char *status, t_env *env)
{
	exit_status = ft_atoi(status);
	if (exit_status >= 0 && exit_status <= 255)
		exit(exit_status);
	else
	{
		exit_status %= 256;
		exit(exit_status);
	}
}

void	ft_exit(char **args, t_env *env)
{
	int	i;

	if (args[1])
	{
		i = 0;
		while (args[1][i])
		{
			if (!ft_isdigit(args[1][i]))
			{
				printf("exit\nminishell: exit: %s: numeric argument required\n", args[1]);
				exit (1);
			}
			i++;
		}
		actualize_status_and_exit(args[1], env);
	}
	else
	{
		exit_status = 0;
		exit(0);
	}
}
