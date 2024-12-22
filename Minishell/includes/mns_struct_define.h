/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_struct_define.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:12:30 by trarijam          #+#    #+#             */
/*   Updated: 2024/12/15 20:24:49 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MNS_STRUCT_DEFINE_H
# define MNS_STRUCT_DEFINE_H

# include <signal.h>

# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"
# define RESET "\033[0m"
# define REDIR_COUNT 0
# define ARG_COUNT 1

typedef enum e_tokentype		t_tokentype;
typedef struct s_token			t_token;
typedef struct s_ast_node		t_ast_node;
typedef struct s_redirection	t_redirection;
typedef enum e_ast_node_type	t_ast_node_type;
typedef struct s_ast_node		t_ast_node;
typedef enum e_type_redirection	t_type_redirection;
typedef struct s_data			t_data;
typedef struct s_exec_status	t_exec_status;

struct	s_exec_status
{
	int			status;
	int			in_pipe;
};

enum e_tokentype
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_IN_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_NEWLINE,
	TOKEN_EOF
};

struct	s_token
{
	t_tokentype		type;
	char			*value;
	int				fd;
	struct s_token	*next;
};

/*structure for AST*/
enum	e_ast_node_type
{
	AST_COMMAND = 0,
	AST_PIPE = 1
};

enum	e_type_redirection
{
	REDIRECTION_IN = 0,
	REDIRECTION_OUT = 1,
	REDIRECTION_APPEND = 2,
	REDIRECTION_HEREDOC = 3,
};

struct	s_redirection
{
	t_type_redirection		type_redirection;
	int						fd;
	char					*target;
};

struct	s_ast_node
{
	t_ast_node_type		type;
	char				**args;
	t_redirection		*redirection;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
};

struct s_data
{
	char				*line;
	char				**envp;
	t_token				*token;
	t_ast_node			*ast;
	int					hist_fd;
	struct sigaction	sa;
	struct sigaction	sa_sigquit;
	struct sigaction	sa_ignore;
	int					exit_status;
	int					fd_tmp;
	char				path[4096];
};

#endif
