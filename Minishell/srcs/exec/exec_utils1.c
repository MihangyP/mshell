/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 07:17:56 by traveloa          #+#    #+#             */
/*   Updated: 2024/10/18 13:11:44 by traveloa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_n_exec_built_in1(char **cmd, char **env, int *flag)
{
	if (ft_strncmp(cmd[0], "export", 7) == 0)
	{
		ft_export(cmd, &env);
		*flag = 0;
		return (1);
	}
	else if (ft_strncmp(cmd[0], "cd", 3) == 0)
	{
		mns_cd(cmd, &env);
		*flag = 0;
		return (1);
	}
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
	{
		ft_unset(cmd, &env);
		*flag = 0;
		return (1);
	}
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
	{
		ft_env(env, cmd);
		*flag = 0;
		return (1);
	}
	return (0);
}

int	check_n_exec_built_in(char **cmd, char **env, t_ast_node *ast, int *flag)
{
	if (ft_strncmp(cmd[0], "pwd", 4) == 0)
	{
		ft_pwd(cmd, env);
		*flag = 0;
		return (1);
	}
	else if (ft_strncmp(cmd[0], "echo", 5) == 0)
	{
		ft_echo(cmd);
		*flag = 0;
		return (1);
	}
	else if (ft_strncmp(cmd[0], "exit", 5) == 0)
	{
		*flag = ft_exit(cmd, ast, env, 0);
		return (1);
	}
	return (0);
}

char	**check_void_cmd(char **cmd, char **envp, t_ast_node *ast)
{
	char	**tmp;
	int		i;

	if (cmd == NULL)
		return (NULL);
	i = 0;
	tmp = cmd;
	while (ft_strlen(tmp[i]) == 0 && tmp[i] != NULL)
		i++;
	if (tmp[i] == NULL)
	{
		free_split(envp);
		free_ast(&ast);
		exit(EXIT_SUCCESS);
	}
	tmp += i;
	return (tmp);
}

void	execute(t_ast_node *ast, char **envp, char **cmd, int *flag)
{
	char			**path_list;
	char			*path;

	(void)ast;
	path_list = find_path_list(envp);
	path = find_path(path_list, cmd[0]);
	if (path_list)
		free_split(path_list);
	if (path == NULL)
	{
		ft_putstr_fd(cmd[0], 2);
		if (ft_strchr(cmd[0], '/') == 0)
			ft_putstr_fd(" : command not found\n", 2);
		else
			ft_putstr_fd(" : No such file or directory\n", 2);
		*flag = 127;
		return ;
	}
	if (execve(path, cmd, envp) == -1)
	{
		if (check_directory_error(path, cmd[0]) == 0)
			perror(cmd[0]);
		*flag = 126;
		return ;
	}
}

void	wait_pipe_cmd(int fd[2], t_exec_status *status, int pid, int pid1)
{
	close(fd[1]);
	close(fd[0]);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, NULL, 0);
	waitpid(pid1, &(status->status), 0);
	if (WIFEXITED(status->status))
		status->status = WEXITSTATUS(status->status);
}
