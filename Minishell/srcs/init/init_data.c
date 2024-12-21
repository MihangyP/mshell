/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:47:58 by trarijam          #+#    #+#             */
/*   Updated: 2024/12/15 12:07:06 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>

static void	get_history(int fd)
{
	char	*line;

	if (fd <= 0)
		return ;
	while (1)
	{
		line = get_next_line(fd);
		if (line != NULL)
		{
			line[ft_strlen(line) - 1] = '\0';
			add_history(line);
			free(line);
		}
		else
			break ;
	}
}

static void	setup_signals(t_data *data)
{
	sigemptyset(&data->sa_sigquit.sa_mask);
	sigemptyset(&data->sa.sa_mask);
	sigemptyset(&data->sa_ignore.sa_mask);
	data->sa.sa_handler = handler_sigint;
	data->sa.sa_flags = 0;
	sigaction(SIGINT, &data->sa, NULL);
	data->sa_ignore.sa_handler = SIG_IGN;
	data->sa_sigquit.sa_flags = 0;
	data->sa_ignore.sa_flags = 0;
	data->sa_sigquit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &data->sa_sigquit, NULL);
}

void	init_data(t_data *data, char **env)
{
	data->line = NULL;
	data->envp = cpy_env(env);
	data->token = NULL;
	data->ast = NULL;
	data->fd_tmp = -1;
	data->exit_status = 0;
	getcwd(data->path, 4096);
	data->hist_fd = open(".history_file", O_RDONLY, 0777);
	if (data->hist_fd > 0)
	{
		get_history(data->hist_fd);
		close(data->hist_fd);
	}
	setup_signals(data);
}
