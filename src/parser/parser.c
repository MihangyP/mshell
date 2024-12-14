/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irazafim <irazafim@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:59:16 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/13 09:57:22 by irazafim         ###   ########.fr       */
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
		if (!parsing_tokens(mshell))
		{
			free_token(&mshell->token);
			free_cmd(&mshell->cmd);
			return (FAIL);
		}
	}
	return (SUCCESS);
}
