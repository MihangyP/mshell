/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:04:33 by trarijam          #+#    #+#             */
/*   Updated: 2024/09/26 10:35:59 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast_node	*parse_token(t_token **tokens, t_ast_node *cmd)
{
	int	counts[3];
	int	count[3];
	int	i;

	i = 0;
	while (i < 3)
	{
		counts[i] = 0;
		count[i] = 0;
		i++;
	}
	count_type_token(*tokens, count);
	init_args_input_output_file(&cmd, count);
	while (tokens != NULL && (*tokens)->type != TOKEN_PIPE
		&& (*tokens)->type != TOKEN_EOF)
	{
		process_token(tokens, cmd, count, counts);
		*tokens = (*tokens)->next;
	}
	set_null_terminators(cmd, count, counts);
	return (cmd);
}

t_ast_node	*parse_command(t_token **tokens)
{
	t_ast_node	*node;

	node = init_node(AST_COMMAND);
	node = parse_token(tokens, node);
	return (node);
}

t_ast_node	*parse_pipeline(t_token **tokens)
{
	t_ast_node	*left;
	t_ast_node	*pipe;

	left = parse_command(tokens);
	if (*tokens != NULL && (*tokens)->type == TOKEN_PIPE)
	{
		pipe = init_node(AST_PIPE);
		pipe->left = left;
		*tokens = (*tokens)->next;
		pipe->right = parse_pipeline(tokens);
		return (pipe);
	}
	return (left);
}

t_ast_node	*parse(t_token *tokens)
{
	t_ast_node	*root;

	root = parse_pipeline(&tokens);
	return (root);
}
