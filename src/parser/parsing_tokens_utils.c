/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tokens_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <pmihangy@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:35:01 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/21 08:56:42 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	print_error(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
	return (1);
}

bool	print_error_token(t_token *token, t_minishell *mshell)
{
	write(2, "syntax error near unexpected token ", 35);
	write(2, "'", 1);
	if (token->next == mshell->token)
		write(2, "newline", 7);
	else
		write(2, token->next->text, ft_strlen(token->next->text));
	write(2, "'\n", 2);
	return (false);
}

int	count_args(t_minishell *mshell, t_token *token)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = token;
	if (tmp->id == CMD || (tmp->id == ARG && \
				tmp->prev != mshell->token->prev && tmp->prev->id > 5))
		count ++;
	tmp = tmp->next;
	while (tmp != mshell->token && tmp->id != PIPE)
	{
		if (tmp->id == CMD || (tmp->id == ARG && \
					tmp->prev != mshell->token->prev && tmp->prev->id > 5))
			count ++;
		tmp = tmp->next;
	}
	return (count);
}

void	*free_cmd_param(char **cmd, int i)
{
	while (--i != -1)
		free(cmd[i]);
	free(cmd);
	return (NULL);
}

int	add_to_cmd_param(char **cmd_param, int *i, char *str)
{
	cmd_param[*i] = ft_strdup(str);
	if (!cmd_param[*i])
		return (0);
	(*i)++;
	return (1);
}
