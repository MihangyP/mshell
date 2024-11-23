/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <pmihangy@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:32:25 by pmihangy          #+#    #+#             */
/*   Updated: 2024/02/27 15:55:23 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	int		diff;
	int		found;

	i = 0;
	diff = 0;
	found = 0;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if ((*(unsigned char *)s1 != *(unsigned char *)s2) && (found == 0))
		{
			diff = (*(unsigned char *)s1 - *(unsigned char *)s2);
			found = 1;
		}
		s1++;
		s2++;
		i++;
	}
	return (diff);
}
