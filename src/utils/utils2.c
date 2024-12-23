/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irazafim <irazafim@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:07:12 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/23 10:07:18 by irazafim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

void	init_quotes(t_quotes *quotes)
{
	quotes->in_single_quote = false;
	quotes->in_double_quote = false;
}

char	*getpath(t_lst *env, char *name)
{
	t_lst	*curr;

	curr = env;
	while (curr->next != env)
	{
		if (!ft_strncmp(name, curr->text, ft_strlen(name)))
			return (curr->text + ft_strlen(name));
		curr = curr->next;
	}
	if (!ft_strncmp(name, curr->text, ft_strlen(name)))
		return (curr->text + ft_strlen(name));
	return (NULL);
}

t_status	my_write_history(t_minishell *mshell, char *entry)
{
	save_history(entry, mshell);
	add_history(entry);
	return (SUCCESS);
}

void	manage_sigint(t_minishell *mshell)
{
	if (g_signal == -69)
		mshell->exit_code = 130;
	g_signal = 0;
}
