/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <pmihangy@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:35:08 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/09 16:19:13 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_cmd	*new_cmd(int infile, int outfile, char **cmd_param)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->skip_cmd = false;
	new->in = infile;
	new->out = outfile;
	new->cmd_param = cmd_param;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_status	append_cmd(t_cmd **cmd, int infile, int outfile, char **cmd_param)
{
	t_cmd	*new;

	new = new_cmd(infile, outfile, cmd_param);
	if (!new)
		return (FAIL);
	if (*cmd == NULL)
	{
		*cmd = new;
		(*cmd)->prev = *cmd;
		(*cmd)->next = *cmd;
		return (SUCCESS);
	}
	new->prev = (*cmd)->prev;
	new->next = (*cmd);
	(*cmd)->prev->next = new;
	(*cmd)->prev = new;
	return (SUCCESS);
}
