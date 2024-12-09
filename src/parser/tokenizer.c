/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:24:10 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/09 14:24:12 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	token_dup(char *entry, int len, char *tmp)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (entry[i] && i < len)
	{
		if (entry[i] && !is_quote(entry[i]))
			tmp[j++] = entry[i++];
		if (entry[i] && is_quote(entry[i]))
		{
			quote = entry[i];
			++i;
			while (entry[i] && entry[i] != quote)
				tmp[j++] = entry[i++];
		}
	}
	tmp[j] = '\0';
}

int	cmd_arg_len(char *entry, int *quotes)
{
	int		i;
	char	quote;

	i = 0;
	while (entry[i] && !is_space(entry[i]) && !is_operator(entry[i]))
	{
		if (entry[i] && !is_quote(entry[i]))
			++i;
		if (is_quote(entry[i]))
		{
			(*quotes)++;
			quote = entry[i++];
			while (entry[i] && entry[i] != quote)
				++i;
			if (entry[i])
				++i;
		}
	}
	return (i);
}

t_status	insert_cmd_arg(t_token **root, char **entry)
{
	char	*tmp;
	int		len;
	int		quotes;
	int		i;

	i = 0;
	quotes = 0;
	len = cmd_arg_len(*entry, &quotes);
	tmp = malloc((len - (2 * quotes) + 1) * sizeof(char));
	if (!tmp)
		return (FAIL);
	token_dup(*entry, len - (2 * quotes), tmp);
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
