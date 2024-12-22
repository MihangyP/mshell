/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traveloa <traveloa@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 08:12:34 by traveloa          #+#    #+#             */
/*   Updated: 2024/09/26 08:12:36 by traveloa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	gnl_ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)s;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

void	*gnl_ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = (char *)malloc(nmemb * size);
	if (!ptr)
		return (0);
	gnl_ft_bzero(ptr, nmemb * size);
	return (ptr);
}

int	gnl_ft_strchr(const char *s, char c)
{
	int				i;
	char			*str;

	str = (char *)s;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*gnl_ft_strjoin(char *s1, char *s2)
{
	char			*str;
	unsigned int	i;
	unsigned int	j;

	str = gnl_ft_calloc((gnl_ft_strlen(s1) + gnl_ft_strlen(s2) + 1),
			sizeof(char));
	if (!str)
		return (0);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	free(s1);
	free(s2);
	return (str);
}

char	*gnl_ft_strcpy(char *src)
{
	size_t	i;
	char	*dest;
	int		len;

	i = 0;
	len = gnl_ft_strlen(src);
	dest = gnl_ft_calloc((len + 1), sizeof(char));
	while (i < gnl_ft_strlen(src))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	free(src);
	return (dest);
}
