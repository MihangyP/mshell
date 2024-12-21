/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:52:34 by trarijam          #+#    #+#             */
/*   Updated: 2024/09/26 10:34:52 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redirection(t_tokentype type)
{
	if (type == TOKEN_HEREDOC || type == TOKEN_REDIR_APPEND
		|| type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_REDIR_IN_OUT)
		return (1);
	return (0);
}

int	is_delimiter(const char *line, const char *heredoc_delimiter)
{
	if (line == NULL)
		return (1);
	if (ft_strncmp(line, heredoc_delimiter,
			ft_strlen(heredoc_delimiter) + 1) == 0)
		return (1);
	return (0);
}

int	is_invalid_redirection(t_token *token)
{
	return (token == NULL || token->type != TOKEN_WORD);
}

int	determine_expansion(t_token *current_token, char *tmp)
{
	if (mns_strcmp(current_token->value, tmp) == 0)
		return (0);
	return (1);
}
