/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <pmihangy@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 09:50:23 by pmihangy          #+#    #+#             */
/*   Updated: 2024/11/28 09:54:48 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void handle_quotes(bool *in_single_quote, bool *in_double_quote, char quote_type)
{
    if (quote_type == '\'')
        *in_single_quote = !(*in_single_quote);
    else if (quote_type == '"')
        *in_double_quote = !(*in_double_quote);
}

t_status append_text(char **result, size_t *result_len, char *text)
{
    *result = str_append(*result, text, result_len);
    if (!(*result))
        return (FAIL);
    return (SUCCESS);
}

t_status handle_env_var(t_minishell *mshell, char **result, size_t *result_len, char **input)
{
    char var_name[256];
    size_t	var_len;

	var_len = 0;
	ft_bzero(var_name, sizeof(var_name));
    if (**input == '?' || ft_isdigit(**input))
        var_name[var_len++] = *(*input)++;
    else
    {
        while (ft_isalpha(**input) || **input == '_')
            var_name[var_len++] = *(*input)++;
    }
    if (!get_var(mshell, result, var_name, result_len))
        return (FAIL);
    return (SUCCESS);
}

t_status	process_quotes(char **input, char **res, size_t *res_len, t_quotes *quotes)
{
	if (**input == '\'' && !quotes->in_double_quote)
	{
		handle_quotes(&quotes->in_single_quote, &quotes->in_double_quote, '\'');
		if (!append_text(res, res_len, "'"))
			return (FAIL);
		(*input)++;
	}
	else if (**input == '"' && !quotes->in_single_quote)
	{
		handle_quotes(&quotes->in_single_quote, &quotes->in_double_quote, '"');
		if (!append_text(res, res_len, "\""))
			return (FAIL);
		(*input)++;
	}
	return (SUCCESS);
}

t_status	process_input(t_minishell *mshell, char *input, char **result, size_t *result_len)
{
	t_quotes	quotes;
	char		tmp[2];

	quotes.in_single_quote = false;
	quotes.in_double_quote = false;
	while (*input)
	{
		if (*input == '\'' || *input == '"')
		{
			if (!process_quotes(&input, result, result_len, &quotes))
				return (FAIL);
		}
		else if (*input == '$' && !quotes.in_single_quote)
		{
			input++;
			if (!handle_env_var(mshell, result, result_len, &input))
				return (FAIL);
		}
		else
		{
			tmp[0] = *(input++);
			tmp[1] = '\0';
			if (!append_text(result, result_len, tmp))
				return (FAIL);
		}
	}
	return (SUCCESS);
}
