#include "../include/minishell.h"

int	exit_status;

void	ft_error(char *error)
{
	perror(error);
	exit(1);
}

//check if input is NULL. if so, it means that readline sent back NULL and that there was
//nothing to read. this handle the case when when ctrl+d is called and exit the program.
//check also if the 1st character of input is a null char. It means that readline read
//something but it is an empty line
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

//before anything else, check if input is exit cmd alone
//if so, exit the program.
//otherwise,, parse and execute the input
void	input_handler(char *input, t_env *env)
{
	t_node *tree;

	is_input_exit(input);
	add_history(input);
	tree = parse_input(input, env);
	check_and_run(tree, env);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_env	*new_env;
	
	(void)av;
	if (ac > 1)
		printf("minishell: program does not require arguments");
	new_env = handle_env(env);
	if (!env)
		return (1);
	exit_status = 0;
	setup_main_signals();
	while (1)
	{
		input = readline("minishell $ ");
		if (!is_input_empty(input))
			input_handler(input, new_env);
	}
	free(new_env);
	return (0);
}
