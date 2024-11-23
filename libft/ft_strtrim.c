/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <pmihangy@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:12:06 by pmihangy          #+#    #+#             */
/*   Updated: 2024/02/27 10:32:12 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in(char const c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char	*empty_string(void)
{
	char	*str;

	str = malloc(sizeof(char));
	if (!str)
		return (NULL);
	str[0] = '\0';
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	len;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (is_in(s1[start], set))
		start++;
	len = ft_strlen(s1);
	end = len - 1;
	if (start == len)
		return (empty_string());
	while (is_in(s1[end], set))
		end--;
	str = malloc((end - start + 2) * sizeof(char));
	if (NULL == str)
		return (NULL);
	ft_strlcpy(str, (s1 + start), (end - start + 2));
	return (str);
}
