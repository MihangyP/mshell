/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:27:11 by trarijam          #+#    #+#             */
/*   Updated: 2024/08/22 15:27:58 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const void *big, const char *little, size_t len)
{
	size_t	i;
	char	*b;

	b = (char *) big;
	if (!*little)
		return (b);
	i = 0;
	while (i < len && b[i] != '\0')
	{
		if (b[i] == little[0])
		{
			if ((ft_strncmp(b + i, little, ft_strlen(little)) == 0)
				&& i + ft_strlen(little) <= len)
				return (b + i);
		}
		i++;
	}
	return (NULL);
}
