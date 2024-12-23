/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irazafim <irazafim@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:28:31 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/23 10:08:43 by irazafim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_sigint(int signum)
{
	(void)signum;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	/*if (g_signal == 0)*/
		/*g_signal = -69;*/
}

void	listen_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	signals2(void)
{
	signal(SIGQUIT, SIG_DFL);
}
