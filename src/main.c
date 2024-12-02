/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irazafim <irazafim@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:13:11 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/02 15:19:07 by irazafim         ###   ########.fr       */
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

bool	make_env2(t_minishell *mshell)
{
	char	path[PATH_MAX];
	char	*tmp;

	tmp = ft_strdup("OLDPWD");
	if (!tmp || !lst_append(&(mshell->env), tmp) || getcwd(path, PATH_MAX) == NULL)
	{
		free_minishell(mshell);
		exit(1);
	}
	tmp = ft_strjoin("PWD=", path);
	if (!tmp || !lst_append(&(mshell->env), tmp))
	{
		free_minishell(mshell);
		exit(1);
	}
	return (1);
}

t_status	repl(t_minishell *mshell)
{
	char	*entry;

	listen_signals();
	while (1)
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
		free_token(&mshell->token);
		free_cmd(&mshell->cmd);
		g_pid = 0;
	}
	return (SUCCESS);
}

t_status	init_env(t_minishell *mshell, char **env)
{
	int		i;
	char	*str;

	 /*TODO: a voir ce que ca fait*/
	if (*env == NULL)
		return (make_env2(mshell));
	i = 0;
	while (env[i])
	{
		str = ft_strdup(env[i]);
		if (!str || !lst_append(&mshell->env, str))
		{
			free_env(&mshell->env);
			return (FAIL);
		}
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
	if (!init_env(&mshell, env) || !repl(&mshell))
	{
		free_minishell(&mshell);
		return (1);
	}
	free_minishell(&mshell);
	return (0);
}
