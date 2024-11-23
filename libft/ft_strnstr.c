/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <pmihangy@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:15:27 by pmihangy          #+#    #+#             */
/*   Updated: 2024/02/26 16:25:48 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	len_n;
	size_t	i;
	size_t	j;

	if (ft_strlen(little) == 0)
		return ((char *) big);
	len_n = ft_strlen(little);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] && big[i + j] == little[j] && i + j < len)
			j++;
		if (j == len_n)
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
