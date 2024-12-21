/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:46:23 by traveloa          #+#    #+#             */
/*   Updated: 2024/10/23 07:18:07 by traveloa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_cmd(char **envp, t_ast_node *ast, t_exec_status *status)
{
	char	**tmp;

	tmp = check_void_cmd(ast->args, envp, ast);
	if (ast->redirection)
		check_redirection_exec(ast, envp, status->in_pipe, 0);
	if (ast->args == NULL)
		return ;
	if (check_n_exec_built_in(tmp, envp, ast, &status->status) == 1
		|| check_n_exec_built_in1(tmp, envp, &status->status) == 1)
		return ;
	execute(ast, envp, tmp, &status->status);
}

void	pipe_exec_left(int fd[2], t_ast_node *ast, char **envp,
					t_exec_status *status)
{
	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
	executor(envp, ast->left, status);
}

int	pipe_exec_right( int fd[2], t_ast_node *ast, char **envp,
					t_exec_status *status)
{
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	executor(envp, ast->right, status);
	return (status->status);
}

void	pipe_cmd(char **envp, t_ast_node *ast, t_exec_status *status)
{
	int			fd[2];
	pid_t		pid;
	pid_t		pid1;

	pid1 = 0;
	if (pipe(fd) == -1)
		return ;
	pid = fork();
	if (pid == 0)
		pipe_exec_left(fd, ast, envp, status);
	else
	{
		pid1 = fork();
		if (pid1 == 0)
		{
			status->in_pipe += 1;
			pipe_exec_right(fd, ast, envp, status);
		}
	}
	wait_pipe_cmd(fd, status, pid, pid1);
}

void	executor(char **envp, t_ast_node *ast, t_exec_status *status)
{
	if (ast->type == 0)
		exec_cmd(envp, ast, status);
	else if (ast->type == 1)
		pipe_cmd(envp, ast, status);
}
