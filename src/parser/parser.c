/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irazafim <irazafim@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:59:16 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/21 18:19:33 by irazafim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_status	expand_entry(t_minishell *mshell, char **entry)
{
	char	*result;
	size_t	result_len;

	result = NULL;
	result_len = 0;
	if (!mshell || !entry || !*entry)
		return (FAIL);
	if (!process_input(mshell, *entry, &result, &result_len))
	{
		free(result);
		return (FAIL);
	}
	free(*entry);
	*entry = result;
	return (SUCCESS);
}

t_status	tokenize_entry(t_token **root, char *entry)
{
	while (*entry)
	{
		while (is_space(*entry))
			++entry;
		if (*entry && !is_operator(*entry))
		{
			if (!insert_cmd_arg(root, &entry))
			{
				if (*root)
					free_token(root);
				return (FAIL);
			}
		}
		else if (*entry && is_operator(*entry))
		{
			if (!insert_operator(root, &entry))
			{
				if (*root)
					free_token(root);
				return (FAIL);
			}
		}
	}
	return (SUCCESS);
}

t_status	check_token_error(t_minishell *mshell)
{
	char	*err_message;

	err_message = NULL;
	if (mshell->token && \
			(mshell->token->prev->id == PIPE || mshell->token->id == PIPE))
	{
		err_message = ft_strdup("Syntax error\n");
		if (!err_message)
			return (FAIL);
		mshell->exit_code = 2;
		write(2, err_message, ft_strlen(err_message));
		free_token(&mshell->token);
		return (FAIL);
	}
	return (SUCCESS);
}

bool	read_in_stdin(t_minishell *mshell, int fd, char *word)
{
	char	*buf;

	while (true)
	{
		buf = NULL;
		buf = readline("> ");
		if (!buf && read_in_stdin_error(word))
			break ;
		if (!ft_strncmp(word, buf, INT_MAX) || g_pid == -42)
			break ;
		if (!expand_entry(mshell, &buf))
			free_and_exit(mshell, 1);
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		free(buf);
	}
	return (free(buf), close(fd), true);
}

int	wait_process(void)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	wait(&status);
	signal(SIGINT, handle_sigint);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 130)
			return (130);
		else
			return (WEXITSTATUS(status));
	}
	return (0);
}

void	handler_sigint_heredoc(int signum)
{
	(void)signum;
	g_pid = 130;
	printf("%d\n", g_pid);
	exit(130);
}

void	setup_signals_heredoc(void)
{
	signal(SIGINT, handler_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_child_process(t_minishell *mshell)
{
	int		status;
	int		fd;
	t_token	*curr;			

	setup_signals_heredoc();
	status = 1;
	curr = mshell->token;
	while (curr->next != mshell->token)
	{
		if (curr->id == HEREDOC)
		{
			fd = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd < 0)
				return ;
			if (!read_in_stdin(mshell, fd, curr->next->text))
			{
				unlink(".heredoc.tmp");
				return ;
			}
			fd = open(".heredoc.tmp", O_RDONLY);
			if (fd > 0)
				unlink(".heredoc.tmp");
		}
		curr = curr->next;
	}
	exit(status);
}

int	heredoc(t_minishell *mshell)
{
	pid_t	pid_child;

	pid_child = fork();
	if (pid_child == -1)
	{
		perror("fork");
		free_and_exit(mshell, 2);
	}
	else if (pid_child == 0)
		handle_child_process(mshell);
	else
		return (wait_process());
	return (0);
}

#if 0
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
#endif

t_status	parse_entry(t_minishell *mshell, char *entry)
{
	if (!expand_entry(mshell, &entry))
		free_and_exit(mshell, 1);
	if (!tokenize_entry(&mshell->token, entry))
		free_and_exit(mshell, 1);
	free(entry);
	if (!check_token_error(mshell))
		return (FAIL);
	if (mshell->token)
	{
		heredoc(mshell);
		printf("g_pid: %d\n", g_pid);
		if (!parsing_tokens(mshell))
		{
			free_token(&mshell->token);
			free_cmd(&mshell->cmd);
			return (FAIL);
		}
	}
	return (SUCCESS);
}
