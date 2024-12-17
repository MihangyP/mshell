/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <pmihangy@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:36:37 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/17 09:49:41 by irazafim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	wait_childrens(t_minishell *mshell)
{
	t_cmd	*curr;
	pid_t	pid;
	int		wstatus;
	int executed_command = 0;

	curr = mshell->cmd;
	while (curr->next != mshell->cmd)
	{
		pid = waitpid(-1, &wstatus, 0);
		executed_command = 1;
		if (pid == g_pid)
		{
			if (WIFEXITED(wstatus))
				mshell->exit_code = WEXITSTATUS(wstatus);
			else if (WIFSIGNALED(wstatus))
				mshell->exit_code = WTERMSIG(wstatus) + 128;
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
			mshell->exit_code = WEXITSTATUS(wstatus);
		else if (WIFSIGNALED(wstatus))
			mshell->exit_code = WTERMSIG(wstatus) + 128;
	}
	if (curr->out >= 0)
		close(curr->out);
	if (curr->in >= 0)
		close(curr->in);
	if (!executed_command && mshell->redirection_error)
	{
		mshell->exit_code = 1;
	}
	mshell->redirection_error = 0;
}

void	free_and_exit(t_minishell *mshell, int exit_code)
{
	free_minishell(mshell);
	exit(exit_code);
}
