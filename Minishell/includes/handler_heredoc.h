/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_heredoc.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 08:41:52 by trarijam          #+#    #+#             */
/*   Updated: 2024/10/16 09:59:15 by traveloa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLER_HEREDOC_H
# define HANDLER_HEREDOC_H

# include "mns_struct_define.h"

typedef struct s_utils_heredoc
{
	char	*tmp_value;
	int		is_expand;
	int		fd;
}	t_utils_heredoc;

/****handler signal***/
void	handler_sigint_heredoc(int sig);

/*heredoc_utils*/
char	*get_name_file(int in_pipe);
int		process_heredoc_redir(t_utils_heredoc utils_var, char **env,
			int exit_status);
int		wait_process(t_data *data);
char	*expand_for_heredoc(char *heredoc_delimiter);
char	*special_expand_char(char *str, char **env, int exit_status);
int		process_tokens_heredoc(t_token *token, t_data *data, int exit_status);
void	setup_signals_heredoc(struct sigaction *sa);
int		process_heredoc_token(t_token **current, t_data *data,
			int exit_status, int in_pipe);
char	*get_result(char *line, int is_expand, char **env, int exit_status);
int		check_delimiter(char *heredoc_delimiter, char *result, char *line);
int		heredoc(t_data *data, int exit_status);

#endif
