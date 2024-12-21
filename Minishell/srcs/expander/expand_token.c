/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:46:46 by trarijam          #+#    #+#             */
/*   Updated: 2024/12/16 17:34:23 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_expand_vars(t_expand_result *result, int *i)
{
	*i = -1;
	result->value = NULL;
	result->create_token = 0;
	result->prev = 0;
}

static void	init_expand_context(t_expand_context *ctx,
			t_expand_result *result, int exit_status)
{
	ctx->result = result;
	ctx->exit_status = exit_status;
	ctx->in_single_quotes = 0;
	ctx->in_double_quotes = 0;
}

static void	expand_char(t_expand_context *ctx)
{
	char	*tmp;

	tmp = expand_special_char(ctx->str, ctx->env, ctx->i, ctx->exit_status);
	ctx->result->value = str_append(ctx->result->value, tmp);
	if (!ctx->in_double_quotes && ctx->result->prev != '=')
		ctx->result->create_token = 1;
	free(tmp);
}

static void	handle_non_expand_char(t_expand_context *ctx, char *str, int i)
{
	if (is_ignored_dollar(str[i], str[i + 1], ctx->in_double_quotes,
			ctx->in_single_quotes) == 1)
		ctx->result->value = char_append(ctx->result->value, str[i]);
}

t_expand_result	expand_token(char *str, char **env, int exit_status)
{
	t_expand_result		result;
	t_expand_context	ctx;
	int					i;

	init_expand_vars(&result, &i);
	init_expand_context(&ctx, &result, exit_status);
	ctx.str = str;
	ctx.env = env;
	ctx.i = &i;
	while (str[++i])
	{
		if (handle_quotes_expander(str[i], &ctx.in_single_quotes,
				&ctx.in_double_quotes) == 1)
			handle_non_expand_char(&ctx, str, i);
		else if (should_expand(str, i, ctx.in_single_quotes))
			expand_char(&ctx);
		else
			handle_non_expand_char(&ctx, str, i);
		ctx.result->prev = str[i];
	}
	result.value = finalize_result(result.value);
	return (result);
}
