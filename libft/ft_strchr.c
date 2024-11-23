/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <pmihangy@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:03:31 by pmihangy          #+#    #+#             */
/*   Updated: 2024/02/28 09:07:47 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
	if (s[i] == (unsigned char)c)
		return ((char *)&s[i]);
	return (NULL);
}
/*char	*ft_strchr(const char *s, int c)*/
/*{*/
	/*while (*s)*/
	/*{*/
		/*if (*(char *)s == (char)c)*/
			/*return ((char *)s);*/
		/*s++;*/
	/*}*/
	/*if (*(char *)s == (char)c)*/
		/*return ((char *)s);*/
	/*return (NULL);*/
/*}*/
