/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:32:05 by trarijam          #+#    #+#             */
/*   Updated: 2024/10/31 07:20:55 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*add_new_token(t_token *expanded_tokens, t_token *new_token,
	t_token **last)
{
	if (expanded_tokens == NULL)
		expanded_tokens = new_token;
	else
		(*last)->next = new_token;
	*last = new_token;
	return (expanded_tokens);
}

t_token	*process_heredoc(t_token *current, t_token *expanded_tokens,
	t_token **last)
{
	t_token	*new_token;
	int		tmp;

	new_token = create_token(current->type, current->value, &tmp, -1);
	expanded_tokens = add_new_token(expanded_tokens, new_token, last);
	return (expanded_tokens);
}

void	init_expand_params(t_expand_params *params, char **env,
	int exit_status, t_token **last)
{
	params->env = env;
	params->exit_status = exit_status;
	params->expanded_tokens = NULL;
	params->last = last;
}

int	process_skip(t_token *current, t_expand_params *params, int flag)
{
	params->expanded_tokens = process_heredoc(current, params->expanded_tokens,
			params->last);
	if (flag == 1)
		return (1);
	return (0);
}

t_token	*expand_tokens(t_token *tokens, char **env, int exit_status)
{
	t_token			*current;
	t_token			*last;
	int				skip_next;
	t_expand_params	params;

	current = tokens;
	last = NULL;
	skip_next = 0;
	init_expand_params(&params, env, exit_status, &last);
	while (current)
	{
		if (skip_next)
			skip_next = process_skip(current, &params, 0);
		else if (current->type == TOKEN_HEREDOC)
			skip_next = process_skip(current, &params, 1);
		else if (current->type == TOKEN_WORD)
			params.expanded_tokens = process_word(current, &params);
		else
			params.expanded_tokens = process_heredoc(current,
					params.expanded_tokens, params.last);
		current = current->next;
	}
	return (params.expanded_tokens);
}
