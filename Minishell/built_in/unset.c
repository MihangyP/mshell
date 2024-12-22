/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:04:05 by traveloa          #+#    #+#             */
/*   Updated: 2024/09/26 10:34:28 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	lst_srch_var(t_list *lst, char *var_name)
{
	char	*tmp;

	while (lst)
	{
		tmp = get_var_name((char *)lst->content);
		if (mns_strcmp(tmp, var_name) == 0)
		{
			free (tmp);
			return (1);
		}
		free (tmp);
		lst = lst->next;
	}
	return (0);
}

void	remove_one(t_list **env_lst, char *to_remove)
{
	t_list	*tmp;
	char	*content;

	tmp = *env_lst;
	if (tmp == NULL || to_remove == NULL)
		return ;
	content = get_var_name((char *)tmp->content);
	if (mns_strcmp(to_remove, content) == 0)
	{
		*env_lst = tmp->next;
		free(content);
		free(tmp->content);
		free(tmp);
	}
	else
	{
		free (content);
		remove_one(&tmp->next, to_remove);
	}
}

int	ft_unset(char **cmd, char ***env)
{
	t_list	*env_lst;
	int		i;

	i = 1;
	env_lst = get_env_lst(*env);
	while (cmd[i])
	{
		remove_one(&env_lst, cmd[i]);
		i++;
	}
	free_split(*env);
	*env = list_to_tab(env_lst);
	free_env_lst(env_lst);
	return (EXIT_SUCCESS);
}
