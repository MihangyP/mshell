/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <pmihangy@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:24:10 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/19 14:12:58 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	token_dup(char *entry, int len, char *tmp, int j)
{
	int	i;

	i = 0;
	while (entry[i + j] && i < len)
	{
		if (entry[i + j] == '\'' && ++j)
		{
			while (entry[i + j] != '\'' && ++i)
				tmp[i - 1] = entry[(i - 1) + j];
			j++;
		}
		else if (entry[i + j] == '"' && ++j)
		{
			while (entry[i + j] != '"' && ++i)
				tmp[i - 1] = entry[(i - 1) + j];
			j++;
		}
		else
		{
			tmp[i] = entry[i + j];
			i++;
		}
	}
	tmp[i] = 0;
}

int	cmd_arg_len(char *entry, int *quotes)
{
	int	i;

	i = 0;
	*quotes = 0;
	while (entry[i] && !is_space(entry[i]) && !is_operator(entry[i]))
	{
		if (entry[i] == '"' || entry[i] == '\'')
		{
			(*quotes)++;
			if (entry[i++] == '"')
				while (entry[i] && entry[i] != '"')
					++i;
			else
				while (entry[i] && entry[i] != '\'')
					++i;
			if (entry[i])
				++i;
		}
		if (entry[i] && entry[i] != '"' && entry[i] != '\'' && \
				!is_space(entry[i]) && !is_operator(entry[i]))
			++i;
	}
	return (i);
}

t_status	insert_cmd_arg(t_token **root, char **entry)
{
	char	*tmp;
	int		len;
	int		quotes;

	quotes = 0;
	len = cmd_arg_len(*entry, &quotes);
	tmp = malloc((len - (2 * quotes) + 1) * sizeof(char));
	if (!tmp)
		return (FAIL);
	token_dup(*entry, len - (2 * quotes), tmp, 0);
	if (!add_token(root, tmp, 0))
		return (free(tmp), FAIL);
	if ((*root)->prev == (*root) || (*root)->prev->prev->id == PIPE)
		(*root)->prev->id = CMD;
	else
		(*root)->prev->id = ARG;
	(*entry) += len;
	return (SUCCESS);
}

void	assign_operator(char **entry, char **op, int *op_type)
{
	if (*(*entry + 1) == **entry)
	{
		if (**entry == '<')
			*op = ft_strdup("<<");
		else
			*op = ft_strdup(">>");
		if (**entry == '<')
			*op_type = HEREDOC;
		else
			*op_type = APPEND;
		(*entry) += 2;
	}
	else
	{
		if (**entry == '<')
			*op = ft_strdup("<");
		else
			*op = ft_strdup(">");
		if (**entry == '<')
			*op_type = INPUT;
		else
			*op_type = TRUNC;
		(*entry)++;
	}
}

t_status	insert_operator(t_token **root, char **entry)
{
	char	*operator;
	int		operator_type;

	operator = NULL;
	operator_type = 0;
	if (**entry == '<' || **entry == '>')
		assign_operator(entry, &operator, &operator_type);
	else if (**entry == '|')
	{
		operator = ft_strdup("|");
		operator_type = PIPE;
		(*entry)++;
	}
	if (operator && !add_token(root, operator, operator_type))
		return (FAIL);
	return (SUCCESS);
}
