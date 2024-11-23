/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <pmihangy@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:25:42 by pmihangy          #+#    #+#             */
/*   Updated: 2024/06/09 15:33:22 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*insert_in_tmp_str(char *tmp_str, char *str, int fd)
{
	int		bytes_rd;

	bytes_rd = 1;
	while (!has_line_break(tmp_str) && bytes_rd != 0)
	{
		bytes_rd = read(fd, str, BUFFER_SIZE);
		if (bytes_rd == -1)
		{
			free(str);
			if (tmp_str)
				free(tmp_str);
			return (NULL);
		}
		str[bytes_rd] = '\0';
		tmp_str = ft_strjoin(tmp_str, str);
	}
	free(str);
	if (NULL == tmp_str || *tmp_str == '\0')
	{
		free(tmp_str);
		return (NULL);
	}
	return (tmp_str);
}

char	*extract_str_line(char *tmp)
{
	int		size;
	int		i;
	char	*str;

	if (NULL == tmp || *tmp == '\0')
		return (NULL);
	size = count_next_line_size(tmp);
	if (0 == size)
		return (NULL);
	str = NULL;
	str = malloc((size + 1) * sizeof(char));
	if (NULL == str)
		return (NULL);
	i = 0;
	while (i < size)
	{
		str[i] = tmp[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*update_tmp_str(char *str)
{
	int		index;
	int		size;
	int		i;
	char	*tmp_str;

	if (NULL == str)
		return (NULL);
	index = count_next_line_size(str);
	size = ft_strlen(str) - index;
	tmp_str = NULL;
	tmp_str = (char *)malloc((size + 1) * sizeof(char));
	if (NULL == tmp_str)
		return (NULL);
	i = 0;
	while (str[index])
	{
		tmp_str[i] = str[index];
		i++;
		index++;
	}
	tmp_str[i] = '\0';
	free(str);
	return (tmp_str);
}

char	*get_next_line(int fd)
{
	static char		*tmp_str = NULL;
	char			*str_next_line;
	char			valid_buffer_size;

	valid_buffer_size = (BUFFER_SIZE > 0 && BUFFER_SIZE < INT_MAX);
	if (fd < 0 || !valid_buffer_size)
		return (NULL);
	str_next_line = NULL;
	str_next_line = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (NULL == str_next_line)
		return (NULL);
	tmp_str = insert_in_tmp_str(tmp_str, str_next_line, fd);
	str_next_line = extract_str_line(tmp_str);
	tmp_str = update_tmp_str(tmp_str);
	return (str_next_line);
}
