/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <pmihangy@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:13:11 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/09 17:54:10 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

pid_t	g_pid;

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

	while (true)
	{
		entry = readline("mshell> ");
		if (!entry)
		{
			printf("exit\n");
			return (free_minishell(mshell), FAIL);
		}
		if (has_open_quote(entry, false, 0))
			printf("open quote\n");
		else if (!is_empty(entry))
		{
			add_history(entry);
			if (!parse_entry(mshell, entry))
				continue ;
			if (!exec_minishell(mshell))
				return (FAIL);
		}
		free_cmd(&mshell->cmd);
		free_token(&mshell->token);
		g_pid = 0;
	}
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
	mshell->pipefd[0] = -1;
	mshell->pipefd[1] = -1;
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
		free_minishell(&mshell);
		return (1);
	}
	free_minishell(&mshell);
	return (0);
}
