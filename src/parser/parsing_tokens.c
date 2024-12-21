/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irazafim <irazafim@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:02:29 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/21 18:20:33 by irazafim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	open_file(t_minishell *mshell, char *filename, int id)
{
	int		flag;
	int		fd;

	(void)mshell;
	if (id == INPUT)
		flag = O_RDONLY;
	else if (id == TRUNC)
		flag = O_CREAT | O_WRONLY | O_TRUNC;
	else if (id == APPEND)
		flag = O_CREAT | O_WRONLY | O_APPEND;
	fd = open(filename, flag, 0644);
	if (fd == -1)
		perror(filename);
	return (fd);
}

t_status	parsing(t_minishell *mshell, t_token *tmp)
{
	if (!get_infile(mshell, tmp, mshell->cmd->prev) && \
		mshell->cmd->prev->in != -1)
		return (FAIL);
	if (mshell->cmd->prev->in == -1)
	{
		mshell->cmd->prev->skip_cmd = true;
		mshell->cmd->prev->out = -1;
		return (close(mshell->fd), SUCCESS);
	}
	if (!get_outfile(tmp, mshell->cmd->prev, mshell) && mshell->cmd->prev->out \
			!= -1)
		return (FAIL);
	if (mshell->cmd->prev->out == -1)
	{
		if (mshell->cmd->prev->in >= 0)
			close(mshell->cmd->prev->in);
		mshell->cmd->prev->skip_cmd = true;
		mshell->cmd->prev->in = -1;
		return (close(mshell->fd), SUCCESS);
	}
	mshell->cmd->prev->cmd_param = get_param(mshell, tmp);
	if (!mshell->cmd->prev->cmd_param)
		free_and_exit(mshell, 1);
	return (SUCCESS);
}

t_status	parsing_tokens(t_minishell *mshell)
{
	t_token	*curr;

	curr = mshell->token;
	if (!append_cmd(&mshell->cmd, -2, -2, NULL))
		free_and_exit(mshell, 1);
	if (!parsing(mshell, curr))
		return (FAIL);
	curr = curr->next;
	while (curr != mshell->token)
	{
		if (curr->prev->id == PIPE)
		{
			if (!append_cmd(&mshell->cmd, -2, -2, NULL))
				free_and_exit(mshell, 1);
			if (!parsing(mshell, curr))
				return (FAIL);
		}
		curr = curr->next;
	}
	return (SUCCESS);
}
