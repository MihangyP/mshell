/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_lexer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:50:11 by trarijam          #+#    #+#             */
/*   Updated: 2024/09/25 15:30:32 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MNS_LEXER_H
# define MNS_LEXER_H

# include "mns_struct_define.h" 

/*********token_utils********* */
void	free_token(t_token *token);
int		is_valid_var_char(char c);
int		valid_name_assignement(const char *value);
int		mns_is_space(char c);
int		is_special_char(char c);
int		get_fd(char *input, int *index);

/**********token creation/manipulation************* */
t_token	*create_token(t_tokentype type, const char *value, int *index,
			int fd);
t_token	*get_next_token(char *input, int *index);

/*******lexer**************/
t_token	*lexer(char *input);

#endif