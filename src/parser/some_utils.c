/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:06:23 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/19 14:07:34 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	callback(int signum)
{
	(void)signum;
	g_pid = -42;
	rl_done = 1;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	printf("mshell");
	rl_on_new_line();
	rl_redisplay();
}

t_status	read_in_stdin_error(char *word)
{
	print_error("warning: here-document delimited by end-of-file ");
	print_error("(wanted '");
	print_error(word);
	print_error("')\n");
	return (SUCCESS);
}
