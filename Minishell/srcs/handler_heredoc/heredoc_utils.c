/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 08:45:04 by trarijam          #+#    #+#             */
/*   Updated: 2024/10/16 08:52:08 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	wait_process(t_data *data)
{
	int	status;

	sigaction(SIGINT, &data->sa_ignore, NULL);
	wait(&status);
	sigaction(SIGINT, &data->sa, NULL);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 130)
			return (130);
		else
			return (WEXITSTATUS(status));
	}
	return (0);
}

void	setup_signals_heredoc(struct sigaction *sa)
{
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = 0;
	sa->sa_handler = handler_sigint_heredoc;
	sigaction(SIGINT, sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

int	process_heredoc_token(t_token **current, t_data *data, int exit_status,
	int in_pipe)
{
	char			*name;
	int				status;
	t_utils_heredoc	utils_heredoc;

	name = NULL;
	utils_heredoc.tmp_value = NULL;
	*current = (*current)->next;
	if (is_invalid_redirection(*current))
		return (-2);
	utils_heredoc.tmp_value = expand_for_heredoc((*current)->value);
	utils_heredoc.is_expand = determine_expansion(*current,
			utils_heredoc.tmp_value);
	name = get_name_file(in_pipe);
	utils_heredoc.fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	status = process_heredoc_redir(utils_heredoc, data->envp, exit_status);
	free(name);
	free(utils_heredoc.tmp_value);
	return (status);
}

char	*get_result(char *line, int is_expand, char **env, int exit_status)
{
	char	*result;

	result = NULL;
	if (line != NULL && is_expand == 0)
		result = special_expand_char(line, env, exit_status);
	else
		result = ft_strdup(line);
	return (result);
}

int	check_delimiter(char *heredoc_delimiter, char *result, char *line)
{
	if (is_delimiter(heredoc_delimiter, result))
	{
		free(line);
		if (result != NULL)
			free(result);
		return (1);
	}
	return (0);
}
