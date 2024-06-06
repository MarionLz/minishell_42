#include "../../include/minishell.h"

void	is_input_exit(char *input, t_data *data)
{
	int		i;
	char	**input_cpy;

	i = 0;
	if (!input)
		return ;
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
			ft_exit_and_free(input_cpy, data);
		}
	}
	free_tab(input_cpy);
	return ;
}

void	ft_exit_and_free(char **input_cpy, t_data *data)
{
	int	i;

	if (input_cpy[1])
	{
		i = 0;
		while (input_cpy[1][i])
		{
			if (!ft_isdigit(input_cpy[1][i]))
			{
				printf("minishell: exit: %s: numeric argument required\n",
					input_cpy[1]);
				free_tab(input_cpy);
				free_tab(data->env_cpy);
				free(data);
				exit (1);
			}
			i++;
		}
	}
	free_tab(input_cpy);
	free_tab(data->env_cpy);
	free(data);
	exit(1);
}

void	actualize_status_and_exit(char *status)
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

void	ft_exit(char **args)
{
	int	i;

	if (args[1])
	{
		i = 0;
		while (args[1][i])
		{
			if (!ft_isdigit(args[1][i]))
			{
				printf("exit\nminishell: exit: %s: numeric argument required\n",
					args[1]);
				exit (1);
			}
			i++;
		}
		actualize_status_and_exit(args[1]);
	}
	else
		exit(0);
}
