/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <pmihangy@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:01:33 by pmihangy          #+#    #+#             */
/*   Updated: 2024/03/15 10:52:53 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void		*ptr;
	size_t		i;

	ptr = (void *)malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < (nmemb * size))
	{
		*(unsigned char *)(ptr + i) = 0;
		i++;
	}
	return (ptr);
}
