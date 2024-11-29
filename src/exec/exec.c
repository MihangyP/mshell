#include <minishell.h>

size_t	len_cmd(t_cmd *list)
{
	t_cmd	*tmp;
	size_t	i;

	if ((list))
	{
		tmp = list;
		i = 1;
		while (tmp->next != list)
		{
			++i;
			tmp = tmp->next;
		}
		return (i);
	}
	return (0);
}

void	signals2(void)
{
	signal(SIGQUIT, SIG_DFL);
}


void	redirect_in_out(t_minishell *mshell, t_cmd *cmd, int *pip)
{
	close(pip[0]);
	if (cmd->in >= 0)
	{
		dup2(cmd->in, 0);
		close(cmd->in);
	}
	if (cmd->out >= 0)
	{
		dup2(cmd->out, 1);
		close(cmd->out);
	}
	else if (cmd->next != mshell->cmd)
		dup2(pip[1], 1);
	close(pip[1]);
}

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
		write(2, (*path), ft_strlen((*path)));
		write(2, " : command not found\n", 21);
		free(*path);
		*path = NULL;
	}
}

void	parent_process(t_minishell *mshell, t_cmd *cmd, int *pip)
{
	if (cmd->in >= 0)
		close(cmd->in);
	if (cmd->in == -2)
		cmd->in = pip[0];
	if (cmd->next != mshell->cmd && cmd->next->in == -2)
		cmd->next->in = pip[0];
	else
		close(pip[0]);
}

bool	cmd_exist(char **path, t_minishell *mshell, char *cmd)
{
	if (!ft_strchr(cmd, '/'))
		*path = find_cmd(mshell, cmd, mshell->env);
	else
		absolute_path(path, cmd, mshell);
	if (!(*path) && mshell->exit_code == -1)
		free_minishell(mshell);
	if (!(*path))
	{
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

void	built(int *pip, t_cmd *cmd, t_minishell *mshell)
{
	close(pip[0]);
	if (cmd->out < 0 && cmd->next != mshell->cmd)
		cmd->out = pip[1];
	else
		close(pip[1]);
	launch_builtin(mshell, cmd);
}

void	child_process(t_minishell *mshell, t_cmd *cmd, int *pip)
{
	char	*path;
	char	**env;

	path = NULL;
	if (cmd->skip_cmd)
		mshell->exit_code = 1;
	else if (is_builtin(cmd->cmd_param[0]))
		built(pip, cmd, mshell);
	else if (cmd_exist(&path, mshell, cmd->cmd_param[0]))
	{
		redirect_in_out(mshell, cmd, pip);
		env = lst_to_arr(mshell->env);
		if (!env)
			free_minishell(mshell);
		rl_clear_history();
		signals2();
		execve(path, cmd->cmd_param, env);
		free(env);
	}
	if (path)
		free(path);
	free_minishell(mshell);
	exit(mshell->exit_code);
}

void	exec_builtin(int save_stdout, t_minishell *mshell, t_cmd *cmd)
{
	if (!ft_strncmp("echo", cmd->cmd_param[0], 69))
		mshell->exit_code = echo_minishell(cmd->cmd_param);
	else if (!ft_strncmp("cd", cmd->cmd_param[0], 69))
		mshell->exit_code = cd_minishell(mshell, cmd->cmd_param);
	else if (!ft_strncmp("pwd", cmd->cmd_param[0], 69))
		mshell->exit_code = pwd_minishell();
	else if (!ft_strncmp("export", cmd->cmd_param[0], 69))
		mshell->exit_code = export_minishell(cmd->cmd_param, &mshell->env);
	else if (!ft_strncmp("unset", cmd->cmd_param[0], 69))
		mshell->exit_code = unset_minishell(cmd->cmd_param, &mshell->env);
	else if (!ft_strncmp("env", cmd->cmd_param[0], 69))
		mshell->exit_code = env_minishell(mshell->env);
	else if (!ft_strncmp("exit", cmd->cmd_param[0], 69))
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

void	wait_all(t_minishell *mshell)
{
	int		status;
	int		pid;
	int		len;
	t_cmd	*tmp;

	tmp = mshell->cmd;
	len = len_cmd(tmp);
	while (len--)
	{
		pid = waitpid(0, &status, 0);
		if (pid == g_pid)
		{
			if (WIFEXITED(status))
				mshell->exit_code = WEXITSTATUS(status);
		}
		if (tmp->out >= 0)
			close(tmp->out);
		if (tmp->in >= 0)
			close(tmp->in);
		tmp = tmp->next;
	}
}

bool	exec_cmd(t_minishell *mshell, t_cmd *cmd, int *pip)
{
	g_pid = fork();
	if (g_pid < 0)
		free_minishell(mshell);
	else if (!g_pid)
	{
		if (cmd->cmd_param && cmd->cmd_param[0])
			child_process(mshell, cmd, pip);
		else
			free_minishell(mshell);
	}
	else
		parent_process(mshell, cmd, pip);
	return (true);
}

bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if (!ft_strncmp("echo", cmd, INT_MAX) || !ft_strncmp("cd", cmd, INT_MAX) \
	|| !ft_strncmp("pwd", cmd, INT_MAX) || !ft_strncmp("export", cmd, INT_MAX) \
	|| !ft_strncmp("unset", cmd, INT_MAX) || !ft_strncmp("env", cmd, INT_MAX) \
	|| !ft_strncmp("exit", cmd, INT_MAX))
		return (true);
	return (false);
}

t_status	exec_minishell(t_minishell *mshell)
{
	t_cmd	*tmp;
	int		*pip;

	pip = mshell->pipefd;
	tmp = mshell->cmd;
	// Simple command like env, pwd, echo Donto, export DONTO=DONTO ..
	if (tmp && tmp->skip_cmd == false && tmp->next == tmp && tmp->cmd_param[0] \
		&& is_builtin(tmp->cmd_param[0]))
		return (launch_builtin(mshell, tmp));
	//--------
	if (pipe(pip) == -1)
		return (FAIL);
	exec_cmd(mshell, tmp, pip);
	tmp = tmp->next;
	while (tmp != mshell->cmd)
	{
		if (pipe(pip) == -1)
			return (-1);
		exec_cmd(mshell, tmp, pip);
		tmp = tmp->next;
	}
	wait_all(mshell);
	return (SUCCESS);
}
