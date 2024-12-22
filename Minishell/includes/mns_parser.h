/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:11:12 by trarijam          #+#    #+#             */
/*   Updated: 2024/09/25 17:18:29 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MNS_PARSER_H
# define MNS_PARSER_H

# include "mns_struct_define.h"

/********fc for free for parser****** */
void		free_ast(t_ast_node **node);

/********init_utils*********** */
t_ast_node	*init_node(t_ast_node_type type);
void		init_args_input_output_file(t_ast_node **cmd, int *count);

/***********parese_utils****** */
void		set_null_terminators(t_ast_node *cmd, int *count, int *counts);
void		process_token(t_token **tokens, t_ast_node *cmd, int *count,
				int *counts);

/**********redirection_utils********** */
void		count_redirection(t_token **tokens, int *count);
void		count_type_token(t_token *tokens, int *count);
void		handle_redirection(t_token **tokens, t_redirection *redirection,
				int *file_count, int count);

/*********parse**************/
t_ast_node	*parse(t_token *tokens);

#endif