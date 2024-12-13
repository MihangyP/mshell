/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irazafim <irazafim@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 09:50:23 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/13 09:29:48 by irazafim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_quotes(bool *in_sq, bool *in_dq, char quote_type)
{
	if (quote_type == '\'')
		*in_sq = !(*in_sq);
	else if (quote_type == '"')
		*in_dq = !(*in_dq);
}

t_status	append_text(char **result, size_t *result_len, char *text)
{
	*result = str_append(*result, text, result_len);
	if (!(*result))
		return (FAIL);
	return (SUCCESS);
}

t_status	chop_var(t_minishell *mshell, char **res, size_t *len, char **input)
{
	char	var_name[256];
	size_t	var_len;

	var_len = 0;
	ft_bzero(var_name, sizeof(var_name));
	if (**input != '?' && !ft_isdigit(**input) && **input != '_' && !ft_isalpha(**input))
	{
		*res = str_append(*res, "$", len);
		return (SUCCESS);
	}
	if (**input == '?' || ft_isdigit(**input))
		var_name[var_len++] = *(*input)++;
	else
	{
		while (ft_isalpha(**input) || **input == '_')
			var_name[var_len++] = *(*input)++;
	}
	if (!get_var(mshell, res, var_name, len))
		return (FAIL);
	return (SUCCESS);
}

t_status	process_quotes(char **input, char **res, size_t *len, t_quotes *q)
{
	if (**input == '\'' && !q->in_double_quote)
	{
		handle_quotes(&q->in_single_quote, &q->in_double_quote, '\'');
		if (!append_text(res, len, "'"))
			return (FAIL);
		(*input)++;
	}
	else if (**input == '"' && !q->in_single_quote)
	{
		handle_quotes(&q->in_single_quote, &q->in_double_quote, '"');
		if (!append_text(res, len, "\""))
			return (FAIL);
		(*input)++;
	}
	return (SUCCESS);
}

// "> >> < * ? [ ] | ; [ ] || && ( ) & # $ \ <<
t_status	process_input(t_minishell *mshell, char *s, char **res, size_t *len)
{
	t_quotes	quotes;
	char		tmp[2];

	init_quotes(&quotes);
	while (*s)
	{
		if ((*s == '\'' || *s == '"') && \
			!process_quotes(&s, res, len, &quotes) && *s)
			return (FAIL);
		else if (*s && *s == '$' && !quotes.in_single_quote)
		{
			s++;
			if (!chop_var(mshell, res, len, &s))
				return (FAIL);
		}
		else if (*s)
		{
			tmp[0] = *(s++);
			tmp[1] = '\0';
			if (!append_text(res, len, tmp))
				return (FAIL);
		}
	}
	return (SUCCESS);
}
