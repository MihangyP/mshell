/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 08:55:11 by trarijam          #+#    #+#             */
/*   Updated: 2024/10/16 08:52:21 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_name_file(int in_pipe)
{
	char	*nb;
	char	*name;

	nb = NULL;
	nb = ft_itoa(in_pipe);
	name = ft_strjoin(".tmp", nb);
	free(nb);
	return (name);
}

char	*expand_for_heredoc(char *heredoc_delimiter)
{
	char	*result;
	int		i;

	result = NULL;
	i = 0;
	while (heredoc_delimiter[i] != '\0')
	{
		if (heredoc_delimiter[i] == '\'' || heredoc_delimiter[i] == '"')
			i++;
		else if (heredoc_delimiter[i] == '$' && (heredoc_delimiter[i + 1]
				== '\'' || heredoc_delimiter[i + 1] == '"'))
			i++;
		else
		{
			result = char_append(result, heredoc_delimiter[i]);
			i++;
		}
	}
	if (result == NULL)
		return (ft_strdup(""));
	return (result);
}

char	*special_expand_char(char *str, char **env, int exit_status)
{
	char	*result;
	char	*tmp;
	int		i;

	i = -1;
	tmp = NULL;
	result = NULL;
	while (str[++i])
	{
		if (str[i] == '$'
			&& (ft_isalnum(str[i + 1]) || str[i + 1] == '_'
				|| str[i + 1] == '?'))
		{
			tmp = expand_special_char(str, env, &i, exit_status);
			result = str_append(result, tmp);
		free(tmp);
		}
		else
			result = char_append(result, str[i]);
	}
	return (result);
}

int	process_tokens_heredoc(t_token *token, t_data *data, int exit_status)
{
	static int	in_pipe;
	int			status;
	t_token		*tmp_token;

	in_pipe = 0;
	status = 0;
	tmp_token = token;
	while (tmp_token)
	{
		if (tmp_token->type == TOKEN_PIPE)
			in_pipe += 1;
		if (tmp_token->type == TOKEN_HEREDOC)
			status = process_heredoc_token(&tmp_token, data, exit_status,
					in_pipe);
		if (status == -2)
			break ;
		tmp_token = tmp_token->next;
	}
	return (status);
}
