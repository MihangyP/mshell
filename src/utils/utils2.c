/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <pmihangy@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:07:12 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/17 09:03:10 by irazafim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

void	init_quotes(t_quotes *quotes)
{
	quotes->in_single_quote = false;
	quotes->in_double_quote = false;
}

char	*getpath(t_lst *env, char *name)
{
	t_lst	*curr;

	curr = env;
	while (curr->next != env)
	{
		if (!ft_strncmp(name, curr->text, ft_strlen(name)))
			return (curr->text + ft_strlen(name));
		curr = curr->next;
	}
	if (!ft_strncmp(name, curr->text, ft_strlen(name)))
		return (curr->text + ft_strlen(name));
	return (NULL);
}
