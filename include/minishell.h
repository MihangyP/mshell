/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irazafim <irazafim@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:13:57 by pmihangy          #+#    #+#             */
/*   Updated: 2024/11/19 13:16:04 by irazafim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* libs */
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <errno.h>
# include <libft.h>

extern pid_t	g_signal_pid;

/* defines structures and enums */

enum	e_id
{
	INPUT = 1,
	HEREDOC,
	TRUNC,
	APPEND,
	PIPE,
	CMD,
	ARG	
};

typedef struct s_token
{
	char			*text;
	enum e_id		id;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_lst
{
	char			*text;
	struct s_lst 	*prev;
	struct s_lst 	*next;
}	t_lst;

typedef struct s_cmd
{
	int				in;
	int				out;
	char			**cmd_param;
	bool			skip_cmd;
	struct s_cmd    *prev;
    struct s_cmd    *next;
}	t_cmd;

typedef struct s_minishell
{
	t_token	*token;
	t_lst	*env;
	t_cmd	*cmd;
	int		exit_code;
	int		pipefd[2];
	bool	sq;
}	t_minishell;


/* prototypes */
bool	has_open_quote(char *entry, bool found_peer, int i);

#endif
