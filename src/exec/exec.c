/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <pmihangy@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:34:31 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/19 09:39:47 by pmihangy         ###   ########.fr       */
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

void	absolute_path(char **path, char *cmd, t_minishell *mshell)
{
	*path = ft_strdup(cmd);
	if (!(*path))
		free_minishell(mshell);
	if (access((*path), F_OK))
	{
		free(*path);
		*path = NULL;
	}
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

bool	cmd_exist(char **path, t_minishell *mshell, char *cmd)
{
	if (!ft_strchr(cmd, '/'))
		*path = find_cmd(mshell, cmd, mshell->env);
	else
		absolute_path(path, cmd, mshell);
	if (!(*path) && mshell->exit_code == -1)
		free_and_exit(mshell, mshell->exit_code);
	if (!(*path))
	{
		if (ft_strchr(cmd, '/') && count_slash(cmd) > 1)
		{
			mshell->exit_code = 126;
			write(2, cmd, ft_strlen(cmd));
			write(2, ": Not a directory\n", 19);
			return (false);
		}
		else if (count_slash(cmd) == 1)
		{
			write(2, cmd, ft_strlen(cmd));
			write(2, ": No such file or directory\n", 28);
		}		
		mshell->exit_code = 127;
		return (false);
	}
	if (access((*path), X_OK))
	{
		perror(*path);
		free((*path));
		(*path) = NULL;
		mshell->exit_code = 126;
		return (false);
	}
	if (!check_dir(path, cmd, mshell))
		return (false);
	return (true);
}

t_status	exec_cmd(t_minishell *mshell, t_cmd *cmd)
{
	int	*fd;

	fd = mshell->pipefd;
	if (pipe(fd) == -1)
		return (FAIL);
	g_pid = fork();
	if (g_pid == 0)
	{
		if (cmd->cmd_param && cmd->cmd_param[0])
			child_process(mshell, cmd, fd);
		else
			free_and_exit(mshell, 0);
	}
	else if (g_pid > 0)
		parent_process(mshell, cmd, fd);
	else
		free_and_exit(mshell, 1);
	return (SUCCESS);
}

t_status	exec_minishell(t_minishell *mshell)
{
	t_cmd	*curr;

	curr = mshell->cmd;
	if (curr && curr->next == curr && !curr->skip_cmd \
		&& curr->cmd_param[0] && is_builtin(curr->cmd_param[0]))
		return (launch_builtin(mshell, curr));
	if (mshell->cmd)
	{
		if (!exec_cmd(mshell, curr))
			return (FAIL);
		curr = curr->next;
		while (curr != mshell->cmd)
		{
			if (!exec_cmd(mshell, curr))
				return (FAIL);
			curr = curr->next;
		}
		wait_childrens(mshell);
	}	
	return (SUCCESS);
}
