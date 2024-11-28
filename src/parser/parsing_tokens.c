/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:02:29 by pmihangy          #+#    #+#             */
/*   Updated: 2024/11/28 12:50:55 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	print_error(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
	return (true);
}

bool	read_in_stdin(t_minishell *mshell, int fd, char *word)
{
	char	*buf;

	while (1)
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
			free_minishell(mshell);
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

bool	print_error_token(t_token *token, t_minishell *mshell)
{
	write(2, "syntax error near unexpected token ", 35);
	write(2, "'", 1);
	if (token->next == mshell->token)
		write(2, "newline", 7);
	else
		write(2, token->next->text, ft_strlen(token->next->text));
	write(2, "'\n", 2);
	return (false);
}

int	count_args(t_minishell *mshell, t_token *token)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = token;
	if (tmp->id == CMD || (tmp->id == ARG && \
		tmp->prev != mshell->token->prev && tmp->prev->id > 5))
		count ++;
	tmp = tmp->next;
	while (tmp != mshell->token && tmp->id != PIPE)
	{
		if (tmp->id == CMD || (tmp->id == ARG && \
		tmp->prev != mshell->token->prev && tmp->prev->id > 5))
			count ++;
		tmp = tmp->next;
	}
	return (count);
}

int	add_to_cmd_param(char **cmd_param, int *i, char *str)
{
	cmd_param[*i] = ft_strdup(str);
	if (!cmd_param[*i])
		return (0);
	(*i)++;
	return (1);
}

void	*free_cmd_param(char **cmd, int i)
{
	while (--i != -1)
		free(cmd[i]);
	free(cmd);
	return (NULL);
}

char	**get_param(t_minishell *mshell, t_token *token)
{
	char	**cmd_param;
	int		i;
	t_token	*tmp;

	i = 0;
	cmd_param = malloc(sizeof(char *) * (count_args(mshell, token) + 1));
	if (cmd_param == NULL)
		return (NULL);
	tmp = token;
	if (tmp->id != PIPE && (tmp->id == CMD || (tmp->id == ARG && \
		tmp->prev != mshell->token->prev && tmp->prev->id > 5)) && \
		!add_to_cmd_param(cmd_param, &i, tmp->text))
		return (free_cmd_param(cmd_param, i));
	tmp = tmp->next;
	while (tmp != mshell->token && tmp->id != PIPE)
	{
		if ((tmp->id == CMD || (tmp->id == ARG && \
			tmp->prev != mshell->token->prev && tmp->prev->id > 5)) && \
			!add_to_cmd_param(cmd_param, &i, tmp->text))
			return (free_cmd_param(cmd_param, i));
		tmp = tmp->next;
	}
	cmd_param[i] = NULL;
	return (cmd_param);
}

int	open_file(t_minishell *mshell, char *filename, int type)
{
	int	fd;

	fd = -2;
	if (type == INPUT)
		fd = open(filename, O_RDONLY, 0644);
	else if (type == HEREDOC)
		fd = here_doc(mshell, filename);
	else if (type == TRUNC)
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (type == APPEND)
		fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (type != HEREDOC && fd < 0)
		perror(filename);
	return (fd);
}

bool	get_out(t_token *tmp, t_cmd *cmd, t_minishell *mshell)
{
	if (tmp->id == TRUNC)
	{
		if (cmd->out >= 0)
			close(cmd->out);
		if (tmp == tmp->next || tmp->next->id <= 5)
			return (print_error_token(tmp, mshell));
		cmd->out = open_file(NULL, tmp->next->text, TRUNC);
		if (cmd->out == -1)
			return (false);
	}
	else if (tmp->id == APPEND)
	{
		if (cmd->out >= 0)
			close(cmd->out);
		if (tmp == tmp->next || tmp->next->id <= 5)
			return (print_error_token(tmp, mshell));
		cmd->out = open_file(NULL, tmp->next->text, APPEND);
		if (cmd->out == -1)
			return (false);
	}
	return (true);
}

bool	get_outfile(t_token *token, t_cmd *cmd, t_minishell *mshell)
{
	t_token	*tmp;

	tmp = token;
	if (tmp->id != PIPE && !get_out(tmp, cmd, mshell))
		return (false);
	tmp = tmp->next;
	while (tmp != mshell->token && tmp->id != PIPE)
	{
		if (!get_out(tmp, cmd, mshell))
			return (false);
		tmp = tmp->next;
	}
	return (true);
}

bool	get_in(t_minishell *mshell, t_token *tmp, t_cmd *cmd)
{
	if (tmp->id == INPUT)
	{
		if (cmd->in >= 0)
			close(cmd->in);
		if (tmp == tmp->next || tmp->next->id <= 5)
			return (print_error_token(tmp, mshell));
		cmd->in = open_file(mshell, tmp->next->text, INPUT);
		if (cmd->in == -1)
			return (false);
	}
	else if (tmp->id == HEREDOC)
	{
		if (cmd->in >= 0)
			close(cmd->in);
		if (tmp == tmp->next || tmp->next->id <= 5)
			return (print_error_token(tmp, mshell));
		cmd->in = open_file(mshell, tmp->next->text, HEREDOC);
		if (cmd->in == -1)
			return (false);
	}
	return (true);
}

bool	get_infile(t_minishell *mshell, t_token *token, t_cmd *cmd)
{
	t_token	*tmp;

	tmp = token;
	if (tmp->id != PIPE && !get_in(mshell, tmp, cmd))
		return (false);
	if (tmp->id == PIPE)
		return (true);
	tmp = tmp->next;
	while (tmp->id != PIPE && tmp != mshell->token)
	{
		if (!get_in(mshell, tmp, cmd))
			return (false);
		tmp = tmp->next;
	}
	return (true);
}

bool	fill_cmd(t_minishell *mshell, t_token *tmp)
{
	if (!get_infile(mshell, tmp, mshell->cmd->prev) && \
		mshell->cmd->prev->in != -1)
		return (false);
	if (mshell->cmd->prev->in == -1)
	{
		mshell->cmd->prev->skip_cmd = true;
		mshell->cmd->prev->out = -1;
		return (true);
	}
	if (!get_outfile(tmp, mshell->cmd->prev, mshell) && mshell->cmd->prev->out \
		!= -1)
		return (false);
	if (mshell->cmd->prev->out == -1)
	{
		if (mshell->cmd->prev->in >= 0)
			close (mshell->cmd->prev->in);
		mshell->cmd->prev->skip_cmd = true;
		mshell->cmd->prev->in = -1;
		return (true);
	}
	mshell->cmd->prev->cmd_param = get_param(mshell, tmp);
	if (!mshell->cmd->prev->cmd_param)
		free_minishell(mshell);
	return (true);
}

bool	norm(t_minishell *mshell, t_token *tmp)
{
	if (!append_cmd(&mshell->cmd, -2, -2, NULL))
		free_minishell(mshell);
	if (!fill_cmd(mshell, tmp))
	{
		mshell->exit_code = 2;
		return (false);
	}
	return (true);
}

t_status	parsing_tokens(t_minishell *mshell)
{
	t_token	*tmp;

	tmp = mshell->token;
	if (!norm(mshell, tmp))
		return (FAIL);
	tmp = tmp->next;
	while (tmp != mshell->token)
	{
		if (tmp->prev->id == PIPE)
		{
			if (!norm(mshell, tmp))
				return (FAIL);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}
