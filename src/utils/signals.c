/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irazafim <irazafim@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:28:31 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/16 08:21:26 by irazafim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_sigint(int signum)
{
	(void)signum;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	if (g_pid == 0)
		rl_redisplay();
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
