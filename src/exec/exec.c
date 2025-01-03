/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irazafim <irazafim@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:34:31 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/23 10:06:46 by irazafim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

bool	cmd_exit_next(char **path, t_minishell *mshell, char *cmd)
{
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
	return (cmd_exit_next(path, mshell, cmd));
}

t_status	exec_cmd(t_minishell *mshell, t_cmd *cmd)
{
	int	*fd;

	fd = mshell->pipefd;
	if (pipe(fd) == -1)
		return (FAIL);
	g_signal = fork();
	if (g_signal == 0)
	{
		if (cmd->cmd_param && cmd->cmd_param[0])
			child_process(mshell, cmd, fd);
		else
			free_and_exit(mshell, 0);
	}
	else if (g_signal > 0)
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
