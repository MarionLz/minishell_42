/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:02:24 by gdaignea          #+#    #+#             */
/*   Updated: 2024/06/11 18:37:51 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
}

void	signal_routine_child(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		g_exit_status = 130;
	}
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
	signal(SIGQUIT, SIG_IGN);
}

//same as above but for when the program is in a here_doc prompt
void	setup_heredoc_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = heredoc_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
