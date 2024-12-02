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
		write(2, (*path), ft_strlen((*path)));
		write(2, " : command not found\n", 21);
		free(*path);
		*path = NULL;
	}
}

bool	cmd_exist(char **path, t_minishell *mshell, char *cmd)
{
	if (!ft_strchr(cmd, '/'))
		*path = find_cmd(mshell, cmd, mshell->env);
	else
		absolute_path(path, cmd, mshell);
	if (!(*path) && mshell->exit_code == -1)
	{
		free_minishell(mshell);
		exit(mshell->exit_code);
	}
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

bool	exec_cmd(t_minishell *mshell, t_cmd *cmd, int *pip)
{
	g_pid = fork();
	if (g_pid < 0)
	{
		free_minishell(mshell);
		exit(1);
	}
	else if (!g_pid)
	{
		if (cmd->cmd_param && cmd->cmd_param[0])
			child_process(mshell, cmd, pip);
		else
		{
			free_minishell(mshell);
			exit(0);
		}
	}
	else
		parent_process(mshell, cmd, pip);
	return (true);
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
