/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 07:27:38 by trarijam          #+#    #+#             */
/*   Updated: 2024/08/22 15:28:01 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	len_substr;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	len_substr = ft_strlen(s) - start;
	if (len < len_substr)
		len_substr = len;
	substr = (char *)malloc(sizeof(char) * len_substr + 1);
	if (substr == NULL)
		return (NULL);
	i = 0;
	while (i < len_substr)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
