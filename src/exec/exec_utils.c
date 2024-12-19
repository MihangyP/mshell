/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:30:14 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/19 14:32:27 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	check_dir(char **path, char *cmd, t_minishell *mshell)
{
	struct stat	path_stat;

	stat(*path, &path_stat);
	if (!S_ISREG(path_stat.st_mode))
	{
		print_error(cmd);
		print_error(" : Is a directory\n");
		mshell->exit_code = 126;
		return (false);
	}
	return (true);
}

int	count_slash(char *cmd)
{
	int	counter;

	counter = 0;
	while (*cmd)
	{
		if (*cmd == '/')
			++counter;
		++cmd;
	}
	return (counter);
}
