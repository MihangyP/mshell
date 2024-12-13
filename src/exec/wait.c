/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <pmihangy@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:36:37 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/09 16:23:05 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	wait_childrens(t_minishell *mshell)
{
	t_cmd	*curr;
	pid_t	pid;
	int		wstatus;

	curr = mshell->cmd;
	while (curr->next != mshell->cmd)
	{
		pid = waitpid(-1, &wstatus, 0);
		if (pid == g_pid)
		{
			if (WIFEXITED(wstatus))
			{
				if (len_cmd(mshell->cmd) > 1)
					mshell->exit_code = WEXITSTATUS(wstatus);
				//if (mshell->exit_code != 1)
				//	mshell->exit_code = WEXITSTATUS(wstatus);
			}
		}
		if (curr->out >= 0)
			close(curr->out);
		if (curr->in >= 0)
			close(curr->in);
		curr = curr->next;
	}
	pid = waitpid(-1, &wstatus, 0);
	if (pid == g_pid)
	{
		if (WIFEXITED(wstatus))
		{
			if (len_cmd(mshell->cmd) > 1)
				mshell->exit_code = WEXITSTATUS(wstatus);
			//if (mshell->exit_code != 1)
			//	mshell->exit_code = WEXITSTATUS(wstatus);
		}
	}
	if (curr->out >= 0)
		close(curr->out);
	if (curr->in >= 0)
		close(curr->in);
}

void	free_and_exit(t_minishell *mshell, int exit_code)
{
	free_minishell(mshell);
	exit(exit_code);
}
