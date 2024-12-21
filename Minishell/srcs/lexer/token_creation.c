/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:39:37 by trarijam          #+#    #+#             */
/*   Updated: 2024/10/07 14:15:18 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*create_token(t_tokentype type, const char *value, int *index,
	int fd)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	if (fd == 1 || fd == 2 || fd == 0)
		token->fd = fd;
	else
		token->fd = 0;
	token->next = NULL;
	if (index != NULL)
		*index += ft_strlen(value);
	return (token);
}

static	void	block_if_for_get_len_word(char *input, int index,
	int	*in_quotes, char *type_quotes)
{
	if (!*in_quotes)
	{
		*in_quotes = 1;
		*type_quotes = input[index];
	}
	else if (input[index] == *type_quotes)
	{
		*in_quotes = 0;
		*type_quotes = 0;
	}
}

static int	get_len_word(char *input, int *index)
{
	int		start;
	int		end;
	int		in_quotes;
	char	type_quotes;

	in_quotes = 0;
	type_quotes = 0;
	start = *index;
	end = start;
	while (input[end] != '\0')
	{
		if (!in_quotes && is_special_char(input[end]) == 1)
			break ;
		if (input[end] == '\'' || input[end] == '"')
			block_if_for_get_len_word(input, end, &in_quotes, &type_quotes);
		end++;
	}
	return (end - start + 1);
}

static t_token	*get_token_word(char *input, int *index)
{
	t_token	*token;
	char	*word;
	int		len;

	len = get_len_word(input, index);
	word = malloc(sizeof(char) * len);
	ft_strlcpy(word, input + *index, len);
	if (word == NULL)
		return (NULL);
	token = create_token(TOKEN_WORD, word, index, -1);
	free(word);
	return (token);
}

t_token	*get_next_token(char *input, int *index)
{
	int	fd;

	fd = get_fd(input, index);
	if (input[*index] == '|')
		return (create_token(TOKEN_PIPE, "|", index, fd));
	else if (input[*index] == '>')
	{
		if (input[*index + 1] == '>')
			return (create_token(TOKEN_REDIR_APPEND, ">>", index, fd));
		return (create_token(TOKEN_REDIR_OUT, ">", index, fd));
	}
	else if (input[*index] == '<')
	{
		if (input[*index + 1] == '>')
			return (create_token(TOKEN_REDIR_IN_OUT, ">", index, fd));
		if (input[*index + 1] == '<')
			return (create_token(TOKEN_HEREDOC, "<<", index, fd));
		return (create_token(TOKEN_REDIR_IN, "<", index, fd));
	}
	else if (input[*index] == '\n')
		return (create_token(TOKEN_NEWLINE, "\n", index, fd));
	else if (input[*index] == '\0')
		return (create_token(TOKEN_EOF, "\0", index, fd));
	else
		return (get_token_word(input, index));
}
