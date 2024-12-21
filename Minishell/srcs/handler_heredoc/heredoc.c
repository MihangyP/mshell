/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:09:13 by trarijam          #+#    #+#             */
/*   Updated: 2024/12/15 20:24:56 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

volatile sig_atomic_t	g_sigint_received = 0;

void	handler_sigint_heredoc(int sig)
{
	(void)sig;
	g_sigint_received = sig;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

int	init_heredoc(char **line, int fd)
{
	*line = readline("heredoc> ");
	if (*line == NULL)
	{
		if (g_sigint_received)
		{
			close(fd);
			return (-1);
		}
		close(fd);
		return (-2);
	}
	return (1);
}

int	process_heredoc_redir(t_utils_heredoc utils_var, char **env,
	int exit_status)
{
	char	*line;
	char	*result;

	line = NULL;
	result = NULL;
	while (1 && utils_var.fd > 0)
	{
		if (init_heredoc(&line, utils_var.fd) < 0)
		{
			if (g_sigint_received == SIGINT)
				return (130);
			return (166);
		}
		result = get_result(line, utils_var.is_expand, env, exit_status);
		if (check_delimiter(utils_var.tmp_value, result, line))
			break ;
		ft_putendl_fd(result, utils_var.fd);
		free(line);
		free(result);
	}
	close(utils_var.fd);
	return (1);
}

void	handle_child_process(t_data *data, int exit_status)
{
	struct sigaction	sa;
	t_token				*token;
	int					status;

	g_sigint_received = 0;
	setup_signals_heredoc(&sa);
	status = 1;
	token = lexer(data->line);
	if (token == NULL)
		exit(status);
	status = process_tokens_heredoc(token, data, exit_status);
	free_token(token);
	free_split(data->envp);
	free(data->line);
	exit(status);
}

int	heredoc(t_data *data, int exit_status)
{
	pid_t	pid_child;

	pid_child = fork();
	if (pid_child == -1)
	{
		perror("fork");
		return (-1);
	}
	else if (pid_child == 0)
		handle_child_process(data, exit_status);
	else
		return (wait_process(data));
	return (0);
}
