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
	t_exec_node *ex_node;

	if (tree->type == EXEC)
	{
		ex_node = (t_exec_node *)tree;
		if ((ft_strncmp(ex_node->args[0], "cd", 2) == 0 && !ex_node->args[0][2]) ||
			(ft_strncmp(ex_node->args[0], "export", 6) == 0 && !ex_node->args[0][6]) ||
			(ft_strncmp(ex_node->args[0], "unset", 5) == 0 && !ex_node->args[0][5]))
			return (1);
		else
			return (0);
	}
	return (0);
}

void	run(t_node *tree, t_env *env)
{
	int	return_status;

	return_status = 0;
	if (tree->type == EXEC)
		run_exec(tree, env);
	else if (tree->type == REDIR)
		run_redir(tree, env);
	else if (tree->type == PIPE)
		return_status = run_pipe(tree, env);
	exit (return_status);
}

void	check_and_run(t_node *tree, t_env *env)
{
	t_exec_node *ex_node;
	pid_t		pid;
	int			status;

	pid = 0;
	if (is_cmd_env_builtin(tree) == 1 && env->nb_cmd == 1)
	{
		ex_node = (t_exec_node *)tree;
		run_builtin(ex_node->args, env);
		exit_status = 0;
	}
	else
	{
		pid = ft_fork();
		if (pid == 0)
			run(tree, env);
		else if (pid > 0)
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
		}
	}
	return ;
}
