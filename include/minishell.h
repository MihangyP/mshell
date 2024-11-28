/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irazafim <irazafim@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:13:57 by pmihangy          #+#    #+#             */
/*   Updated: 2024/11/26 14:55:33 by irazafim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

extern pid_t	g_pid;

typedef bool	t_status;
# define SUCCESS true
# define FAIL false

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

/* error */
bool	has_open_quote(char *entry, bool found_peer, int i);

/* free */
void	free_2d_arr(char **arr);
void	free_token(t_token **token);
void	free_cmd(t_cmd **list);
void	free_env(t_lst **list);
void	free_minishell(t_minishell	*mshell);

/* lst */
t_status	lst_append(t_lst **env, char *str);
size_t	len_list(t_lst *list);
char	**lst_to_arr(t_lst *env);

/* signals */
void	listen_signals(void);

/* utils */
bool	is_empty(const char *str);
int		is_space(const char c);
bool	is_operator(char c);
void	sort_array(char **arr, int len);

/* */
bool	print_error(char *str);

/* parser */
t_status	parse_entry(t_minishell *mshell, char *entry);

/* expander */
t_status	expand_entry(t_minishell *mshell, char **entry);
char	*get_env_value(t_minishell *mshell, const char *key);
char	*str_append(char *dest, const char *src, size_t *dest_len);
t_status get_var(t_minishell *mshell, char **result, char *var_name, size_t *result_len);

/* tokenizer */
t_status	insert_operator(t_token **root, char **entry);
t_status	insert_cmd_arg(t_token **root, char **entry);
int	cmd_arg_len(char *entry, int *quotes);
void	copy_token(char *entry, int length, char *str, int i);
int	token_new_elem(t_token **new, char *str, int type);
void	add_first(t_token **list, t_token *new);
int	append_token(t_token **list, char *str, int type);
void	print_token(t_token *token);

/* parsing tokens*/
bool	parsing_tokens(t_minishell *mshell);

/* exec */
bool	exec_minishell(t_minishell *mshell);
char	*find_cmd(t_minishell *mshell, char *sample, t_lst *env);
bool	launch_builtin(t_minishell *mshell, t_cmd *cmd);
bool	is_builtin(char *cmd);

/* builtins */
int	ft_cd(t_minishell *mshell, char **params);
int	ft_echo(char **args);
int	ft_env(t_lst *env);
void	ft_exit(t_minishell *mshell, char **args);
int	ft_export(char **str, t_lst **env);
int	ft_pwd(void);
int	ft_unset(char **str, t_lst **env);

int	exist(char *str, t_lst *env);
bool	export(char *str, t_lst **env);

#endif
