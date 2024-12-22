/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:21:37 by trarijam          #+#    #+#             */
/*   Updated: 2024/08/22 15:27:59 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last_occurence;

	last_occurence = (void *)0;
	while (*s)
	{
		if (*s == (char)c)
			last_occurence = (char *)s;
		s++;
	}
	if (c == '\0')
	{
		if (*s == '\0')
			last_occurence = (char *)s;
	}
	return (last_occurence);
}
