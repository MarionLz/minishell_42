#include "../include/minishell.h"

void	signal_routine(int signal)
{
	if (signal == SIGINT && g_exit_status != -42)
	{
		g_exit_status = 130;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signal == SIGQUIT)
		return ;
}

void	heredoc_handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		printf("\n");
		unlink(".here_doc");
		close(STDIN_FILENO);
		g_exit_status = 130;
		exit (g_exit_status);
	}
	else if (signal == SIGQUIT)
		g_exit_status = 0;
}

//initialize sigaction structure for when ctrl+d and 
//ctrl+c are called in the main program
//structure is defined is signal.h lib
//ctrl+c = sigint
//ctrl+d = sigquit
void	setup_main_signals(void)
{
	struct sigaction	sa_main;

	sa_main.sa_handler = signal_routine;
	sigemptyset(&sa_main.sa_mask);
	sa_main.sa_flags = 0;
	sigaction(SIGINT, &sa_main, NULL);
	sigaction(SIGQUIT, &sa_main, NULL);
}

//same as above but for when the program is in a here_doc prompt
void	setup_heredoc_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = heredoc_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
