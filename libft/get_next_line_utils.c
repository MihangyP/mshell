/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <pmihangy@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:57:56 by pmihangy          #+#    #+#             */
/*   Updated: 2024/06/09 15:25:26 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	has_line_break(char *str)
{
	int	i;

	if (NULL == str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	count_next_line_size(char *tmp)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (NULL == tmp)
		return (0);
	while (tmp[i])
	{
		if (tmp[i] == '\n')
		{
			count++;
			break ;
		}
		count++;
		i++;
	}
	return (count);
}
