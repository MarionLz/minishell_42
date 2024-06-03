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
		if (ft_strncmp(ex_node->args[0], "cd", 2) == 0 ||
			ft_strncmp(ex_node->args[0], "export", 6) == 0 ||
			ft_strncmp(ex_node->args[0], "unset", 5) == 0)
			return (1);
		else
			return (0);
	}
	return (0);
}

//function that is called recursively to run cmd accordingly to the pipes and redirection
//that are in the input.
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

//check 1st if the cmd to be runned is a builtin involving to modify the environment.
// if so, run them before forking so the program always remember what is modified on env.
//(as parent don't inherite of what's done in child)
//otherwise, fork, run the cmd and wait for the process to be done properly.
//while (waitpid) ensure that it will know that the process is done.
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
			while (waitpid(pid, &status, 0) == -1)
				;
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
		}
	}
	return ;
}
