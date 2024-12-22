/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traveloa <traveloa@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 08:12:16 by traveloa          #+#    #+#             */
/*   Updated: 2024/09/26 08:12:17 by traveloa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*get_line(char *line)
{
	size_t	i;
	size_t	j;
	char	*ret;

	i = 0;
	j = 0;
	if (line == 0)
		return (0);
	while (line[i] != '\n' && line[i])
		i++;
	ret = gnl_ft_calloc((i + 2), sizeof(char));
	while (j <= i)
	{
		ret[j] = line[j];
		j++;
	}
	free(line);
	return (ret);
}

char	*get_rest(char *line)
{
	size_t	i;
	char	*rest;
	size_t	j;

	i = 0;
	j = 0;
	if (line == 0)
		return (0);
	while (line[i] != '\n' && line[i])
		i++;
	rest = gnl_ft_calloc((gnl_ft_strlen(line) - i + 1), sizeof(char));
	while (i < gnl_ft_strlen(line))
	{
		rest[j] = line[i + 1];
		i++;
		j++;
	}
	rest[j] = '\0';
	return (rest);
}

char	*ft_read(int fd, char *rest, ssize_t n)
{
	char	*line;

	if (rest != 0)
		line = gnl_ft_strcpy(rest);
	else
		line = gnl_ft_calloc(1, 1);
	while (n > 0 && gnl_ft_strchr(line, '\n') == 0)
	{
		rest = gnl_ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		n = read(fd, rest, BUFFER_SIZE);
		if (n <= 0)
		{
			free(rest);
			if (gnl_ft_strlen(line) > 0)
				return (line);
			free(line);
			rest = 0;
			return (0);
		}
		rest[BUFFER_SIZE] = '\0';
		line = gnl_ft_strjoin(line, rest);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		*rest;
	ssize_t			n;

	if (BUFFER_SIZE == 0 || fd < 0)
		return (0);
	n = 1;
	line = ft_read(fd, rest, n);
	rest = get_rest(line);
	line = get_line(line);
	return (line);
}
