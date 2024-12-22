/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_check_tokens.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:37:00 by trarijam          #+#    #+#             */
/*   Updated: 2024/10/15 13:51:13 by traveloa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MNS_CHECK_TOKENS_H
# define MNS_CHECK_TOKENS_H

# include "mns_struct_define.h"

/*******utils*************/
int	is_redirection(t_tokentype type);
int	is_delimiter(const char *line, const char *heredoc_delimiter);
int	is_invalid_redirection(t_token *token);
int	determine_expansion(t_token *current_token, char *tmp);

/***handle_heredoc**/
int	handle_heredoc(t_token **current_token, char **env, int exit_status);

/*******analyze_tokens*******/
int	print_syntax_error(void);
int	analyze_tokens(t_token *tokens);

#endif
