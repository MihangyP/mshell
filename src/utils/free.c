/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmihangy <pmihangy@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:28:13 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/19 09:29:43 by pmihangy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_2d_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			free(arr[i++]);
		free(arr);
	}
	arr = NULL;
}

void	free_token(t_token **token)
{
	t_token	*curr;
	t_token	*tmp;

	if (*token == NULL)
		return ;
	curr = *token;
	while (curr->next != *token)
	{
		tmp = curr;
		curr = curr->next;
		free(tmp->text);
		free(tmp);
	}
	free(curr->text);
	free(curr);
	*token = NULL;
}

static void	free_inside_cmd(t_cmd *tmp)
{
	if (tmp->in > 0)
		close(tmp->in);
	tmp->in = -2;
	if (tmp->out > 0)
		close(tmp->out);
	tmp->out = -2;
	free_2d_arr(tmp->cmd_param);
}

void	free_cmd(t_cmd **list)
{
	t_cmd	*tmp;
	t_cmd	*current;

	if (!(*list))
		return ;
	current = *list;
	while (current->next != *list)
	{
		tmp = current;
		current = current->next;
		free_inside_cmd(tmp);
		free(tmp);
	}
	free_inside_cmd(current);
	free(current);
	*list = NULL;
}

void	free_env(t_lst **list)
{
	t_lst	*curr;
	t_lst	*tmp;

	if (*list == NULL)
		return ;
	curr = *list;
	while (curr->next != *list)
	{
		tmp = curr;
		curr = curr->next;
		free(tmp->text);
		free(tmp);
	}
	free(curr->text);
	free(curr);
	*list = NULL;
}
