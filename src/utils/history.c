/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irazafim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:03:37 by irazafim          #+#    #+#             */
/*   Updated: 2024/12/16 14:21:58 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		++i;
	}
    free(arr);
}

int open_history_file(void)
{
    int fd;

    fd = open(HISTORY_FILE, O_CREAT | O_RDWR, 0666);
    if (fd < 0)
        exit(1);
    return (fd);
}

void    save_history(char *entry, int fd)
{
    char    *to_append;

    to_append = ft_strjoin(entry, "\n");
    if (!to_append)
        exit(1);
    write(fd, to_append, ft_strlen(to_append));
    free(to_append);
}

void    load_history(int fd)
{
    char    **arr;
	char	*s;
    int     i;
	struct stat	file_stat;

	stat(HISTORY_FILE, &file_stat);
	s = malloc(file_stat.st_size * sizeof(char));
	if (!s)
		exit(1);
    if (read(fd, s, file_stat.st_size) == -1)
		exit(1);
    arr = ft_split(s, '\n');
	if (!arr)
		exit(1);
    i = -1;
    while (arr[++i])
		add_history(arr[i]);
	free_arr(arr);
}
