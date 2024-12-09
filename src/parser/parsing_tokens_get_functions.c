/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tokens_get_functions.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <pmihangy@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:27:52 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/09 16:20:46 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**get_param(t_minishell *mshell, t_token *token)
{
	char	**cmd_param;
	int		i;
	t_token	*tmp;

	i = 0;
	cmd_param = malloc(sizeof(char *) * (count_args(mshell, token) + 1));
	if (cmd_param == NULL)
		return (NULL);
	tmp = token;
	if (tmp->id != PIPE && (tmp->id == CMD || (tmp->id == ARG && \
					tmp->prev != mshell->token->prev && tmp->prev->id > 5)) && \
			!add_to_cmd_param(cmd_param, &i, tmp->text))
		return (free_cmd_param(cmd_param, i));
	tmp = tmp->next;
	while (tmp != mshell->token && tmp->id != PIPE)
	{
		if ((tmp->id == CMD || (tmp->id == ARG && \
			tmp->prev != mshell->token->prev && tmp->prev->id > 5)) && \
				!add_to_cmd_param(cmd_param, &i, tmp->text))
			return (free_cmd_param(cmd_param, i));
		tmp = tmp->next;
	}
	cmd_param[i] = NULL;
	return (cmd_param);
}

t_status	get_in(t_minishell *mshell, t_token *tmp, t_cmd *cmd)
{
	if (tmp->id == INPUT)
	{
		if (cmd->in >= 0)
			close(cmd->in);
		if (tmp == tmp->next || tmp->next->id <= 5)
			return (print_error_token(tmp, mshell));
		cmd->in = open_file(mshell, tmp->next->text, INPUT);
		if (cmd->in == -1)
			return (FAIL);
	}
	else if (tmp->id == HEREDOC)
	{
		if (cmd->in >= 0)
			close(cmd->in);
		if (tmp == tmp->next || tmp->next->id <= 5)
			return (print_error_token(tmp, mshell));
		cmd->in = open_file(mshell, tmp->next->text, HEREDOC);
		if (cmd->in == -1)
			return (FAIL);
	}
	return (SUCCESS);
}

t_status	get_out(t_token *tmp, t_cmd *cmd, t_minishell *mshell)
{
	if (tmp->id == TRUNC)
	{
		if (cmd->out >= 0)
			close(cmd->out);
		if (tmp == tmp->next || tmp->next->id <= 5)
			return (print_error_token(tmp, mshell));
		cmd->out = open_file(NULL, tmp->next->text, TRUNC);
		if (cmd->out == -1)
			return (FAIL);
	}
	else if (tmp->id == APPEND)
	{
		if (cmd->out >= 0)
			close(cmd->out);
		if (tmp == tmp->next || tmp->next->id <= 5)
			return (print_error_token(tmp, mshell));
		cmd->out = open_file(NULL, tmp->next->text, APPEND);
		if (cmd->out == -1)
			return (FAIL);
	}
	return (SUCCESS);
}

t_status	get_outfile(t_token *token, t_cmd *cmd, t_minishell *mshell)
{
	t_token	*tmp;

	tmp = token;
	if (tmp->id != PIPE && !get_out(tmp, cmd, mshell))
		return (FAIL);
	tmp = tmp->next;
	while (tmp != mshell->token && tmp->id != PIPE)
	{
		if (!get_out(tmp, cmd, mshell))
			return (FAIL);
		tmp = tmp->next;
	}
	return (SUCCESS);
}

t_status	get_infile(t_minishell *mshell, t_token *token, t_cmd *cmd)
{
	t_token	*tmp;

	tmp = token;
	if (tmp->id != PIPE && !get_in(mshell, tmp, cmd))
		return (FAIL);
	if (tmp->id == PIPE)
		return (SUCCESS);
	tmp = tmp->next;
	while (tmp->id != PIPE && tmp != mshell->token)
	{
		if (!get_in(mshell, tmp, cmd))
			return (FAIL);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
