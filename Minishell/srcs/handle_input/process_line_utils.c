/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:52:51 by trarijam          #+#    #+#             */
/*   Updated: 2024/12/15 20:25:31 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <fcntl.h>

int	check_eof(char *str)
{
	if (*str == '\0')
	{
		free(str);
		return (1);
	}
	return (0);
}

void	uptdate_history(t_data *data)
{
	char	*path;
	char	*tmp;

	add_history(data->line);
	tmp = ft_strjoin(data->path, "/");
	path = ft_strjoin(tmp, ".history_file");
	data->hist_fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (data->hist_fd != -1)
	{
		ft_putendl_fd(data->line, data->hist_fd);
		close(data->hist_fd);
	}
	free(path);
	free(tmp);
}

int	check_built_in(t_ast_node *ast)
{
	if (ft_strncmp(ast->args[0], "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(ast->args[0], "export", 7) == 0)
		return (1);
	else if (ft_strncmp(ast->args[0], "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(ast->args[0], "exit", 5) == 0)
		return (1);
	else
		return (0);
}

void	execute_fork_cmd(t_data *data, char **envp, t_ast_node *ast)
{
	pid_t			pid;
	t_exec_status	status;

	status.status = 0;
	status.in_pipe = 0;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		executor(envp, ast, &status);
		free_ast(&ast);
		free_split(envp);
		exit(status.status);
	}
	else
		wait_child_process(data);
}

void	handle_ast(t_data *data)
{
	if (data->ast->type == AST_COMMAND && data->ast->args != NULL
		&& check_built_in(data->ast) == 1)
		handle_built_in_cmd(data->ast, &data->envp, data);
	else
		execute_fork_cmd(data, data->envp, data->ast);
}
