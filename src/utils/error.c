/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <pmihangy@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:29:27 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/21 09:41:26 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	has_not_quote(char *entry)
{
	int	i;

	i = 0;
	while (entry[i])
	{
		if (entry[i] == '\'' || entry[i] == '\"')
			return (false);
		++i;
	}
	return (true);
}

bool	has_open_quote(char *entry, bool found_peer, int i)
{
	char	quote;

	if (i == 0 && has_not_quote(entry))
		return (false);
	if (!entry[i] && found_peer)
		return (false);
	while (entry[i] && entry[i] != '\'' && entry[i] != '\"')
		++i;
	if (entry[i])
	{
		quote = entry[i];
		found_peer = false;
	}
	else
		return (false);
	++i;
	while (entry[i] && entry[i] != quote)
		++i;
	if (entry[i])
		found_peer = true;
	else
		return (true);
	return (has_open_quote(entry, found_peer, i + 1));
}

void	free_arr(char **arr)
{
	int	i;

	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
