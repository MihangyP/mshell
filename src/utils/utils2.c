/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:07:12 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/09 14:29:02 by pmihangy         ###   ########.fr       */
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
