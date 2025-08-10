/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:13:33 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/04 17:52:18 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_handler_child(int sig)
{
	if (sig == SIGINT)
	{
		g_signals = SIGINT;
		printf("\n");
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		g_signals = SIGQUIT;
		printf("Quit (core dumped)\n");
		rl_redisplay();
	}
}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_signals = SIGINT;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		g_signals = SIGQUIT;
		rl_redisplay();
	}
}

void	sig_handler_hd(int sig)
{
	if (sig == SIGINT)
	{
		g_signals = SIGINT;
		close(0);
	}
	if (sig == SIGQUIT)
	{
		g_signals = SIGQUIT;
		rl_redisplay();
	}
}
