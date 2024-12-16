/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irazafim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:03:37 by irazafim          #+#    #+#             */
/*   Updated: 2024/12/16 12:07:45 by irazafim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int open_history_file(void)
{
    int fd;

    fd = open(HISTORY_FILE, O_CREAT | O_RDWR, 0666);
    if (fd < 0)
        exit(1);
    return (fd);
}

void    save_history(char *entry, int old_fd)
{
    char    *to_append;
    int     fd;

    close(old_fd);
    fd = open(HISTORY_FILE, O_WRONLY | O_APPEND);
    if (fd < 0)
        exit(1);
    to_append = ft_strjoin(entry, "\n");
    if (!to_append)
        exit(1);
    write(fd, to_append, ft_strlen(to_append));
    free(to_append);
    close(fd);
}

void    load_history(int old_fd)
{
    int     fd;
    char    **arr;
	char	*s;
    int     i;
	struct stat	file_stat;

    close(old_fd);
	stat(HISTORY_FILE, &file_stat);
	s = malloc(file_stat.st_size * sizeof(char));
	if (!s)
		exit(1);
    fd = open(HISTORY_FILE, O_RDONLY);
    if (fd < 1)
        exit(1);
    if (read(fd, s, file_stat.st_size) == -1)
		exit(1);
    arr = ft_split(s, '\n');
	if (!arr)
		exit(1);
    i = -1;
    while (arr[++i])
		add_history(arr[i]);
	close(fd);
}
