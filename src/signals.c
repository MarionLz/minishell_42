#include "../include/minishell.h"

void	signal_routine(int signal)
{
	if (signal == SIGINT && exit_status != -42)
	{
		exit_status = 130;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signal == SIGQUIT)
		;
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
		exit_status = 130;
		exit (exit_status);
	}
	else if (signal == SIGQUIT)
		exit_status = 0;
} 

//initialize sigaction structure for when ctrl+d and ctrl+c are called in the main program
//structure is defined is signal.h lib
//ctrl+c = sigint
//ctrl+d = sigquit
void setup_main_signals(void) 
{
	struct sigaction sa_main;

	sa_main.sa_handler = signal_routine; // Définir le gestionnaire pour SIGINT
	sigemptyset(&sa_main.sa_mask);      // Initialiser le masque de signaux
	sa_main.sa_flags = 0;               // Définir les flags (0 par défaut)
	sigaction(SIGINT, &sa_main, NULL);  // Installer le gestionnaire pour SIGINT
	sigaction(SIGQUIT, &sa_main, NULL);  // Installer le gestionnaire pour SIGQUIT
}

//same as above but for when the program is in a here_doc prompt
void setup_heredoc_signals(void) 
{
	struct sigaction sa;

	sa.sa_handler = heredoc_handler;  // Définir le gestionnaire de signal
	sigemptyset(&sa.sa_mask);         // Initialiser le masque de signaux
	sa.sa_flags = 0;                  // Définir les flags (0 par défaut)
	sigaction(SIGINT, &sa, NULL);     // Installer le gestionnaire pour SIGINT
	sigaction(SIGQUIT, &sa, NULL);    // Installer le gestionnaire pour SIGQUIT
}
