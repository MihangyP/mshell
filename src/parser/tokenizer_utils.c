/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:38:45 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/09 13:50:31 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*new_token(char *text, int id)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new || !text)
		return (NULL);
	new->text = text;
	new->id = id;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

t_status	add_token(t_token **token, char *text, int id)
{
	t_token	*new;

	new = new_token(text, id);
	if (!new)
		return (free(text), FAIL);
	if (*token == NULL)
	{
		(*token) = new;
		(*token)->prev = *token;
		(*token)->next = *token;
		return (SUCCESS);
	}
	new->prev = (*token)->prev;
	new->next = (*token);
	(*token)->prev->next = new;
	(*token)->prev = new;
	return (SUCCESS);
}

void	print_token(t_token *token)
{
	t_token	*curr;

	if (token == NULL)
		return ;
	curr = token;
	while (curr->next != token)
	{
		printf("text: %s, id: %d\n", curr->text, curr->id);
		curr = curr->next;
	}
	printf("text: %s, id: %d\n", curr->text, curr->id);
}
