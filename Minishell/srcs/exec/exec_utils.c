/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:41:54 by traveloa          #+#    #+#             */
/*   Updated: 2024/10/31 07:21:47 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**find_path_list(char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		tmp = ft_strnstr(env[i], "PATH", 4);
		if (tmp != 0)
			break ;
		i++;
	}
	if (tmp)
		return (ft_split(tmp + 5, ':'));
	else
		return (NULL);
}

char	*check_path(char **path_list, char *cmd)
{
	int		i;
	char	*path;
	char	*tmp;

	i = 0;
	if (path_list == NULL)
		return (NULL);
	while (path_list[i])
	{
		tmp = ft_strjoin(path_list[i], "/");
		path = ft_strjoin(tmp, cmd);
		if (access(path, F_OK) == 0)
		{
			free(tmp);
			return (path);
		}
		else
		{
			free(tmp);
			free(path);
			i++;
		}
	}
	return (0);
}

char	*find_path(char **path_list, char *cmd)
{
	if (cmd == 0)
		return (0);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (cmd);
		return (0);
	}
	return (check_path(path_list, cmd));
}

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	check_directory_error(char *path, char *cmd)
{
	struct stat		stats;

	stat(path, &stats);
	if (S_ISDIR(stats.st_mode))
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(" : Is a directory", 2);
		return (1);
	}
	return (0);
}
