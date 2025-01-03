/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <pmihangy@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:35:25 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/21 08:59:12 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if (!ft_strncmp("echo", cmd, INT_MAX))
		return (true);
	else if (!ft_strncmp("cd", cmd, INT_MAX))
		return (true);
	else if (!ft_strncmp("pwd", cmd, INT_MAX))
		return (true);
	else if (!ft_strncmp("unset", cmd, INT_MAX))
		return (true);
	else if (!ft_strncmp("export", cmd, INT_MAX))
		return (true);
	else if (!ft_strncmp("env", cmd, INT_MAX))
		return (true);
	else if (!ft_strncmp("exit", cmd, INT_MAX))
		return (true);
	return (false);
}

void	manage_env(t_minishell *mshell, t_cmd *cmd)
{
	if (cmd->cmd_param[1])
	{
		write(2, "No such file or directory\n", 26);
		mshell->exit_code = 127;
	}
	else
		mshell->exit_code = env_minishell(mshell->env);
}

void	exec_builtin(int save_stdout, t_minishell *mshell, t_cmd *cmd)
{
	if (!ft_strncmp("echo", cmd->cmd_param[0], INT_MAX))
		mshell->exit_code = echo_minishell(cmd->cmd_param);
	else if (!ft_strncmp("cd", cmd->cmd_param[0], INT_MAX))
		mshell->exit_code = cd_minishell(mshell, cmd->cmd_param);
	else if (!ft_strncmp("pwd", cmd->cmd_param[0], INT_MAX))
		mshell->exit_code = pwd_minishell();
	else if (!ft_strncmp("export", cmd->cmd_param[0], INT_MAX))
		mshell->exit_code = export_minishell(cmd->cmd_param, &mshell->env);
	else if (!ft_strncmp("unset", cmd->cmd_param[0], INT_MAX))
		mshell->exit_code = unset_minishell(cmd->cmd_param, &mshell->env);
	else if (!ft_strncmp("env", cmd->cmd_param[0], INT_MAX))
		manage_env(mshell, cmd);
	else if (!ft_strncmp("exit", cmd->cmd_param[0], INT_MAX))
	{
		if (cmd->out >= 0)
		{
			dup2(save_stdout, 1);
			close(save_stdout);
		}
		exit_minishell(mshell, cmd->cmd_param);
	}
}

bool	launch_builtin(t_minishell *mshell, t_cmd *cmd)
{
	int	save_stdout;

	save_stdout = -1;
	if (cmd->out >= 0)
	{
		save_stdout = dup(1);
		dup2(cmd->out, 1);
	}
	exec_builtin(save_stdout, mshell, cmd);
	if (cmd->out >= 0)
	{
		dup2(save_stdout, 1);
		close (save_stdout);
	}
	return (true);
}

void	built(int *pip, t_cmd *cmd, t_minishell *mshell)
{
	close(pip[0]);
	if (cmd->out < 0 && cmd->next != mshell->cmd)
		cmd->out = pip[1];
	else
		close(pip[1]);
	launch_builtin(mshell, cmd);
}
