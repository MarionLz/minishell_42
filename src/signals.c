#include "../include/minishell.h"

void	sigint_routine(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_sigint(void)
{
	struct sigaction	s_sigaction;

	s_sigaction.sa_handler = sigint_routine;
	sigaction(SIGINT, &s_sigaction, 0);
}

void	handle_sigquit(void)
{
	struct sigaction	s_sigaction;

	s_sigaction.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &s_sigaction, 0);
}
