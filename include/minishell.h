/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irazafim <irazafim@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:13:57 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/17 08:58:50 by irazafim         ###   ########.fr       */
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
# define HISTORY_FILE ".mshell_history"

typedef struct s_quotes
{
	bool	in_single_quote;
	bool	in_double_quote;
}	t_quotes;

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
	struct s_lst	*prev;
	struct s_lst	*next;
}	t_lst;

typedef struct s_cmd
{
	int				in;
	int				out;
	char			**cmd_param;
	bool			skip_cmd;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_minishell
{
	t_token	*token;
	t_lst	*env;
	t_cmd	*cmd;
	int		exit_code;
	int		redirection_error;
	int		pipefd[2];
}	t_minishell;

char	*get_next(int fd);
/* error */
bool		has_open_quote(char *entry, bool found_peer, int i);

/* free */
void		free_2d_arr(char **arr);
void		free_token(t_token **token);
void		free_cmd(t_cmd **list);
void		free_env(t_lst **list);
void		free_minishell(t_minishell	*mshell);

/* lst */
t_status	lst_append(t_lst **env, char *str);
size_t		len_list(t_lst *list);
char		**lst_to_arr(t_lst *env);

/* signals */
void		listen_signals(void);
void		signals2(void);

/* utils */
bool		is_empty(const char *str);
int			is_space(const char c);
bool		is_operator(char c);
void		sort_array(char **arr, int len);
bool		is_quote(char c);
void		free_and_exit(t_minishell *mshell, int exit_code);
void		init_quotes(t_quotes *quotes);
int		len_cmd(t_cmd *cmd);
int open_history_file(void);
void    save_history(char *entry, int old_fd);
void    load_history(int old_fd);
char	*getpath(t_lst *env, char *name);

/* */
bool		print_error(char *str);
bool		print_error_token(t_token *token, t_minishell *mshell);

/* parser */
t_status	parse_entry(t_minishell *mshell, char *entry);

/* expander */
t_status	expand_entry(t_minishell *mshell, char **entry);
char		*get_env_value(t_minishell *mshell, const char *key);
char		*str_append(char *dest, const char *src, size_t *dest_len);
t_status	get_var(t_minishell *mshell, char **result, \
			char *var_name, size_t *result_len);
void		handle_quotes(bool *in_single_quote, bool *in_double_quote, \
			char quote_type);
t_status	append_text(char **result, size_t *result_len, char *text);
t_status	handle_env_var(t_minishell *mshell, char **result, \
			size_t *result_len, char **input);
t_status	process_quotes(char **input, char **res, size_t *res_len, \
			t_quotes *quotes);
t_status	process_input(t_minishell *mshell, char *input, char **result, \
			size_t *result_len);

/* tokenizer */
t_status	insert_operator(t_token **root, char **entry);
t_status	insert_cmd_arg(t_token **root, char **entry);
int			cmd_arg_len(char *entry, int *quotes);
void		copy_token(char *entry, int length, char *str, int i);
t_status	add_token(t_token **token, char *text, int id);
void		print_token(t_token *token);

/* parsing tokens*/
bool		parsing_tokens(t_minishell *mshell);
t_status	append_cmd(t_cmd **cmd, int infile, int outfile, char **cmd_param);
bool		read_in_stdin(t_minishell *mshell, int fd, char *word);
int			here_doc(t_minishell *mshell, char *word);
int			open_file(t_minishell *mshell, char *filename, int id);
int			count_args(t_minishell *mshell, t_token *token);
void		*free_cmd_param(char **cmd, int i);
int			add_to_cmd_param(char **cmd_param, int *i, char *str);
char		**get_param(t_minishell *mshell, t_token *token);
t_status	get_in(t_minishell *mshell, t_token *tmp, t_cmd *cmd);
t_status	get_out(t_token *tmp, t_cmd *cmd, t_minishell *mshell);
t_status	get_outfile(t_token *token, t_cmd *cmd, t_minishell *mshell);
t_status	get_infile(t_minishell *mshell, t_token *token, t_cmd *cmd);

/* exec */
bool		exec_minishell(t_minishell *mshell);
char		*find_cmd(t_minishell *mshell, char *sample, t_lst *env);
bool		launch_builtin(t_minishell *mshell, t_cmd *cmd);
bool		is_builtin(char *cmd);
void		exec_builtin(int save_stdout, t_minishell *mshell, t_cmd *cmd);
bool		launch_builtin(t_minishell *mshell, t_cmd *cmd);
void		built(int *pip, t_cmd *cmd, t_minishell *mshell);
void		redirect_in_out(t_minishell *mshell, t_cmd *cmd, int *pip);
void		child_process(t_minishell *mshell, t_cmd *cmd, int *pip);
void		parent_process(t_minishell *mshell, t_cmd *cmd, int *pip);
bool		cmd_exist(char **path, t_minishell *mshell, char *cmd);
void		wait_childrens(t_minishell *mshell);

/* builtins */
int			cd_minishell(t_minishell *mshell, char **params);
int			echo_minishell(char **args);
int			env_minishell(t_lst *env);
void		exit_minishell(t_minishell *mshell, char **args);
int			export_minishell(char **str, t_lst **env);
bool		valid_identifier(char *str);
char		*get_key(char *str);
bool		exist_in_env(char *key, t_lst *env);
char		*get_str(char *s, char *to_exp, char *key);
t_status	fill_env_text(char *s1, char *s2, t_lst *new_env);
int			pwd_minishell(void);
int			unset_minishell(char **str, t_lst **env);

int			exist(char *str, t_lst *env);
bool		export(char *str, t_lst **env);

#endif
