/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <pmihangy@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:19:43 by pmihangy          #+#    #+#             */
/*   Updated: 2024/02/26 14:37:05 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last_occ;

	last_occ = NULL;
	while (*s)
	{
		if ((char)c == *s)
			last_occ = (char *)s;
		s++;
	}
	if (*s == (char)c)
		last_occ = (char *)s;
	return (last_occ);
}
