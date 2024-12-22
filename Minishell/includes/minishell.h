/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 08:44:10 by trarijam          #+#    #+#             */
/*   Updated: 2024/12/16 17:15:04 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "mns_built_in.h"
# include "mns_executor.h"
# include "mns_utils_built_in.h"
# include "utils_minishell.h"
# include "mns_struct_define.h"
# include "mns_lexer.h"
# include "mns_expander.h"
# include "mns_parser.h"
# include "mns_check_tokens.h"
# include "handler_heredoc.h"
# include "../libft/libft.h"
# include "../libft/get_next_line/get_next_line.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/stat.h>

int		line_is_space(char *line);
int		handle_exit(t_data *data);
void	close_tmp(void);
void	process_line(t_data *data);
int		handle_state(int state);
int		process_input(t_data *data);
void	cleanup_data(t_data *data);
char	*expand_line(char *line, char **env, int exit_status);
void	handler_sigint(int sig);
int		check_eof(char *str);
void	uptdate_history(t_data *data);
int		check_built_in(t_ast_node *ast);
void	wait_child_process(t_data *data);
void	execute_fork_cmd(t_data *data, char **envp, t_ast_node *ast);
void	init_data(t_data *data, char **env);
void	remove_one(t_list **env_lst, char *to_remove);	
char	*get_var_value(char *var);

int		handle_value(int value);
void	set_variable(int value);
int		get_variable(void);
char	*remove_quotes(char *str);

#endif
