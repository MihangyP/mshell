/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irazafim <irazafim@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:02:29 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/13 11:14:42 by irazafim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	read_in_stdin(t_minishell *mshell, int fd, char *word)
{
	char	*buf;

	while (true)
	{
		buf = NULL;
		buf = readline("> ");
		if (!buf)
		{
			print_error("warning: here-document delimited by end-of-file ");
			print_error("(wanted '");
			print_error(word);
			print_error("')\n");
			break ;
		}
		if (!ft_strncmp(word, buf, INT_MAX))
			break ;
		if (!expand_entry(mshell, &buf))
			free_and_exit(mshell, 1);
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		free(buf);
	}
	free(buf);
	close(fd);
	return (true);
}

int	here_doc(t_minishell *mshell, char *word)
{
	int	fd;

	fd = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	if (!read_in_stdin(mshell, fd, word))
	{
		unlink(".heredoc.tmp");
		return (-1);
	}
	fd = open(".heredoc.tmp", O_RDONLY);
	if (fd > 0)
		unlink(".heredoc.tmp");
	return (fd);
}

int	open_file(t_minishell *mshell, char *filename, int id)
{
	int		flag;
	int		fd;

	if (id == INPUT)
		flag = O_RDONLY;
	else if (id == TRUNC)
		flag = O_CREAT | O_WRONLY | O_TRUNC;
	else if (id == APPEND)
		flag = O_CREAT | O_WRONLY | O_APPEND;
	else if (id == HEREDOC)
		return (here_doc(mshell, filename));
	else
		return (-2);
	fd = open(filename, flag, 0644);
	if (fd == -1)
	{
		mshell->exit_code = 1;
		perror(filename);
	}
	return (fd);
}

t_status	parsing(t_minishell *mshell, t_token *tmp)
{
	bool	infile = get_infile(mshell, tmp, mshell->cmd->prev);

	if (!infile && mshell->cmd->prev->in != -1)
		return (FAIL);
	if (mshell->cmd->prev->in == -1)
	{
		mshell->cmd->prev->skip_cmd = true;
		mshell->cmd->prev->out = -1;
		return (SUCCESS);
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
		return (SUCCESS);
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
