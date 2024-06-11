/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malauzie <malauzie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:02:01 by gdaignea          #+#    #+#             */
/*   Updated: 2024/06/11 17:38:29 by malauzie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		ft_error("fork");
	return (pid);
}

int	is_cmd_env_builtin(t_node *tree)
{
	t_exec_node	*ex_node;

	if (tree->type == EXEC)
	{
		ex_node = (t_exec_node *)tree;
		if ((ft_strncmp(ex_node->args[0], "cd", 2) == 0
				&& !ex_node->args[0][2]) ||
			(ft_strncmp(ex_node->args[0], "export", 6) == 0
				&& !ex_node->args[0][6]) ||
			(ft_strncmp(ex_node->args[0], "unset", 5) == 0
				&& !ex_node->args[0][5]))
			return (1);
		else
			return (0);
	}
	return (0);
}

//function that is called recursively to run cmd 
//accordingly to the pipes and redirection that are in 
//the input.
void	run(t_node *tree, t_data *data)
{
	int	return_status;

	return_status = 0;
	if (tree->type == EXEC)
		run_exec(tree, data);
	else if (tree->type == REDIR)
		run_redir(tree, data);
	else if (tree->type == PIPE)
		return_status = run_pipe(tree, data);
	exit (return_status);
}

void	fork_before_exec(t_node *tree, t_data *data)
{
	pid_t	pid;
	int		status;

	pid = 0;
	pid = ft_fork();
	signal(SIGINT, signal_routine_child);
	if (pid == 0)
		run(tree, data);
	else if (pid > 0)
	{
		while (waitpid(pid, &status, 0) == -1)
			;
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
	}
}

//check 1st if the cmd to be runned is a builtin involving 
//to modify the environment.
//if so, run them before forking so the program always remember 
//what is modified on env.
//(as parent don't inherite of what's done in child)
//otherwise, fork, run the cmd and wait for the process to be done properly.
//while (waitpid) ensure that it will know that the process is done.
void	check_and_run(t_node *tree, t_data *data)
{
	t_exec_node	*ex_node;

	if (is_cmd_env_builtin(tree) == 1 && data->nb_cmd == 1)
	{
		ex_node = (t_exec_node *)tree;
		run_builtin(ex_node->args, data);
		g_exit_status = 0;
	}
	else
		fork_before_exec(tree, data);
	return ;
}
