/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <pmihangy@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:28:43 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/21 10:44:37 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_space(const char c)
{
	return (c == 32 || (c > 8 && c < 14));
}

bool	is_empty(const char *str)
{
	while (*str && is_space(*str))
		++str;
	if (*str)
		return (false);
	return (true);
}

bool	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}
