/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 08:49:38 by trarijam          #+#    #+#             */
/*   Updated: 2024/08/22 15:24:12 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_src;
	size_t	len_dst;
	size_t	j;
	size_t	res;

	len_dst = 0;
	while (dst[len_dst] != '\0')
		len_dst++;
	len_src = 0;
	while (src[len_src] != '\0')
		len_src++;
	if (size == 0)
		return (len_src);
	if (len_dst >= size)
		return (len_src + size);
	j = 0;
	res = len_dst + len_src;
	while (src[j] != '\0' && len_dst + j < size -1)
	{
		dst[len_dst + j] = src[j];
		j++;
	}
	dst[len_dst + j] = '\0';
	return (res);
}
