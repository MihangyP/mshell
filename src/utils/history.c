/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irazafim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:03:37 by irazafim          #+#    #+#             */
/*   Updated: 2024/12/19 13:53:03 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	open_history_file(void)
{
	int	fd;

	fd = open(HISTORY_FILE, O_CREAT | O_RDWR, 0666);
	if (fd < 0)
		exit(1);
	return (fd);
}

void	save_history(char *entry, t_minishell *mshell)
{
	char	*to_append;

	to_append = ft_strjoin(entry, "\n");
	if (!to_append)
		exit(1);
	if (mshell->fd < 0)
		mshell->fd = open(HISTORY_FILE, O_RDWR | O_APPEND);
	write(mshell->fd, to_append, ft_strlen(to_append));
	free(to_append);
}

void	load_history(int fd)
{
	char	*s;

	s = get_next(fd);
	while (s)
	{
		add_history(s);
		free(s);
		s = get_next(fd);
	}
	free(s);
}
