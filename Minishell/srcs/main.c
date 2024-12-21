/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:30:35 by trarijam          #+#    #+#             */
/*   Updated: 2024/12/15 20:25:51 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handler_sigint(int sig)
{
	(void)sig;
	set_variable(130);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	handle_built_in_cmd(t_ast_node *ast, char ***envp, t_data *data)
{
	int		fd_in;
	int		fd_out;

	fd_in = dup(STDIN_FILENO);
	fd_out = dup(STDOUT_FILENO);
	if (ast->redirection && check_redirection_exec(ast, *envp, 0, 1) == 0)
	{
		data->exit_status = 1;
		mns_close_fds(fd_in, fd_out);
		return ;
	}
	if (ft_strncmp(ast->args[0], "cd", 3) == 0)
		data->exit_status = mns_cd(ast->args, envp);
	else if (ft_strncmp(ast->args[0], "export", 7) == 0)
		data->exit_status = ft_export(ast->args, envp);
	else if (ft_strncmp(ast->args[0], "unset", 6) == 0)
		data->exit_status = ft_unset(ast->args, envp);
	else if (ft_strncmp(ast->args[0], "exit", 5) == 0)
	{
		mns_close_fds(fd_in, fd_out);
		data->exit_status = ft_exit(ast->args, ast, *envp, 1);
	}
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	mns_close_fds(fd_in, fd_out);
}

void	wait_child_process(t_data *data)
{
	int	status;

	sigaction(SIGINT, &data->sa_ignore, NULL);
	wait(&status);
	sigaction(SIGINT, &data->sa, NULL);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		write(1, "\n", 1);
		data->exit_status = 128 + WTERMSIG(status);
	}
}

void	process_line(t_data *data)
{
	t_token		*expanded;

	data->token = lexer(data->line);
	if (data->token == NULL)
	{
		data->ast = NULL;
		return ;
	}
	if (analyze_tokens(data->token) == 0)
	{
		close_tmp();
		free_token(data->token);
		data->exit_status = 2;
		return ;
	}
	expanded = expand_tokens(data->token, data->envp, data->exit_status);
	free_token(data->token);
	data->ast = parse(expanded);
	free_token(expanded);
	if (data->ast->type == AST_COMMAND && data->ast->args != NULL
		&& data->ast->args[0] == NULL)
		return ;
	handle_ast(data);
}

int	main(int argc, char **argv, char **env)
{
	int		tmp;
	t_data	data;

	(void)argc;
	(void)argv;
	init_data(&data, env);
	ft_putstr_fd("\033]2;667\007", STDIN_FILENO);
	while (1)
	{
		set_variable(0);
		data.line = readline("minishell$ ");
		if (data.line == NULL)
			return (handle_exit(&data));
		tmp = process_input(&data);
		if (tmp == 1)
		{
			data.exit_status = 130;
			continue ;
		}
		else if (tmp == 2)
			continue ;
		cleanup_data(&data);
	}
	return (0);
}
