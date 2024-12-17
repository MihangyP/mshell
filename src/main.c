/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <pmihangy@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:13:11 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/17 13:17:23 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

pid_t	g_pid;

int	len_cmd(t_cmd *cmd)
{
	t_cmd	*curr = cmd;
	int	counter = 0;

	while (curr->next != cmd)
	{
		++counter;
		curr = curr->next;
	}
	++counter;
	return (counter);
}

void	free_minishell(t_minishell	*mshell)
{
	if (mshell->token)
		free_token(&mshell->token);
	if (mshell->cmd)
		free_cmd(&mshell->cmd);
	if (mshell->env)
		free_env(&mshell->env);
	if (mshell->pipefd[0] > 0)
		close(mshell->pipefd[0]);
	if (mshell->pipefd[1] > 0)
		close(mshell->pipefd[1]);
	rl_clear_history();
	if (!access(".heredoc.tmp", F_OK))
		unlink(".heredoc.tmp");
}

t_status	repl(t_minishell *mshell)
{
	char	*entry;

	load_history(mshell->fd);
	while (true)
	{
		entry = readline("mshell> ");
		if (g_pid == -69)
			mshell->exit_code = 130;
		if (!entry)
		{
			printf("exit\n");
			close(mshell->fd);
			free_minishell(mshell);
			return (1);
		}
		if (has_open_quote(entry, false, 0))
			printf("open quote\n");
		else if (!is_empty(entry))
		{
			save_history(entry, mshell->fd);
			add_history(entry);
			if (!parse_entry(mshell, entry))
			{
				close(mshell->fd);
				continue ;
			}
			if (!exec_minishell(mshell))
				return (close(mshell->fd), FAIL);
		}
		free_cmd(&mshell->cmd);
		free_token(&mshell->token);
		g_pid = 0;
	}
	close(mshell->fd);
	return (SUCCESS);
}

t_status	init_env(t_minishell *mshell, char **env)
{
	int		i;
	char	*str;

	if (*env == NULL)
		return (SUCCESS);
	i = 0;
	while (env[i])
	{
		str = ft_strdup(env[i]);
		if (!str || !lst_append(&mshell->env, str))
		{
			free_env(&mshell->env);
			return (FAIL);
		}
		free(str);
		++i;
	}
	return (SUCCESS);
}

void	init_minishell(t_minishell *mshell)
{
	mshell->token = NULL;
	mshell->env = NULL;
	mshell->cmd = NULL;
	mshell->exit_code = 0;
	mshell->redirection_error = 0;
	mshell->pipefd[0] = -1;
	mshell->pipefd[1] = -1;
	mshell->fd = open_history_file();
	g_pid = 0;
}

int	main(int ac, char **av, char **env)
{
	t_minishell	mshell;

	(void)ac;
	(void)av;
	init_minishell(&mshell);
	listen_signals();
	if (!init_env(&mshell, env) || !repl(&mshell))
	{
		close(mshell.fd);
		free_minishell(&mshell);
		return (1);
	}
	close(mshell.fd);
	free_minishell(&mshell);
	return (0);
}
