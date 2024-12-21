/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 07:13:33 by traveloa          #+#    #+#             */
/*   Updated: 2024/10/22 09:12:39 by traveloa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redir_input(char *input, t_ast_node *node, char **envp, int flag)
{
	int	fd;

	fd = open(input, O_RDONLY);
	if (fd < 0)
	{
		perror (input);
		if (flag == 1)
			return (0);
		free_ast(&node);
		free_split(envp);
		exit(EXIT_FAILURE);
	}
	dup2(fd, 0);
	close(fd);
	return (1);
}

int	redir_output(char *output, t_ast_node *node, char **envp, int flag)
{
	int	fd;

	fd = open(output, O_RDONLY | O_WRONLY | O_CREAT
			| O_TRUNC, 0644);
	if (fd < 0)
	{
		perror (output);
		if (flag == 1)
			return (0);
		free_ast(&node);
		free_split(envp);
		exit (EXIT_FAILURE);
	}
	dup2(fd, 1);
	close(fd);
	return (1);
}

int	output_append(char *out_append, t_ast_node *node, char **envp, int flag)
{
	int	fd;

	fd = open(out_append, O_RDONLY | O_WRONLY
			| O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror (out_append);
		if (flag == 1)
			return (0);
		free_ast(&node);
		free_split(envp);
		exit (EXIT_FAILURE);
	}
	dup2(fd, 1);
	close(fd);
	return (1);
}

int	here_doc(int in_pipe, t_ast_node *node, char **envp, int flag)
{
	char	*nb;
	char	*name;
	int		fd;

	nb = ft_itoa(in_pipe);
	name = ft_strjoin(".tmp", nb);
	fd = open(name, O_RDONLY);
	free(name);
	free(nb);
	if (fd < 0)
	{
		perror ("heredoc");
		if (flag == 1)
			return (0);
		free_ast(&node);
		free_split(envp);
		exit (EXIT_FAILURE);
	}
	dup2(fd, 0);
	close(fd);
	return (1);
}

int	check_redirection_exec(t_ast_node *ast, char **envp, int in_pipe, int flag)
{
	int	i;
	int	status;

	i = 0;
	status = 1;
	while (ast->redirection[i].target)
	{
		if (status == 0)
			return (status);
		if (ast->redirection[i].type_redirection == REDIRECTION_IN)
			status = redir_input(ast->redirection[i].target, ast, envp, flag);
		else if (ast->redirection[i].type_redirection == REDIRECTION_OUT)
			status = redir_output(ast->redirection[i].target, ast, envp, flag);
		else if (ast->redirection[i].type_redirection == REDIRECTION_APPEND)
			status = output_append(ast->redirection[i].target, ast, envp, flag);
		else if (ast->redirection[i].type_redirection == REDIRECTION_HEREDOC)
			status = here_doc(in_pipe, ast, envp, flag);
		i++;
	}
	return (status);
}
